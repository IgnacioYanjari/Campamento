#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

template <typename T>
struct vec {
    T x, y;
    vec(){}
    vec(T _x, T _y) : x(_x), y(_y){}
};

template <typename T>
struct point{
    T x, y;
    point(){}
    point(T _x, T _y) : x(_x), y(_y){}
};

// should be replaced for Point structure in the future
template <typename T>
vec<T> toVec(T x1, T y1, T x2, T y2){
    return vec<T>(x2-x1, y2-y1);
}

template <typename T>
vec<T> toVec(point<T> p, point<T> q){
    return vec<T>(q.x-p.x, q.y-p.y);
}

// CCW (Counter clockwise) test.
// returns -1 if the point is on one side of the line,
// 0 if the point lies in the line,
// 1 if the point is on the other side of the line
template <typename T>
int ccw(point<T> p, point<T> q, point<T> r){
    T position = cross(toVec(p, q), toVec(p, r));
    if(position < 0) return -1;
    else if(position > 0) return 1;
    else return 0;
}

// Cross product between vectors (vec)
template <typename T>
T cross(vec<T> a, vec<T> b){
    return (a.x*b.y - a.y*b.x);
}

// Return true if a point (p3) lies on segment p1p2
template <typename T>
bool onSegment(point<T> p1, point<T> p2, point<T> p3){
    if((min(p1.x,p2.x) <= p3.x && p3.x <= max(p1.x,p2.x))
        && (min(p1.y,p2.y) <= p3.y && p3.y <= max(p1.y,p2.y)))
        return true;
    else return false;
}

// Two line segments intersect if and only if either (or both) conditions
// holds:
// 1. Each segment straddles the line containing the other. (straddle = atravesar)
// 2. An endpoint of one segment lies on the other segment.
template <typename T>
bool segmentsIntersect(point<T> p1, point<T> p2, point<T> p3, point<T> p4){
    int orientation1, orientation2, orientation3, orientation4;
    orientation1 = ccw(p1,p2,p3);
    orientation2 = ccw(p1,p2,p4);
    orientation3 = ccw(p3,p4,p1);
    orientation4 = ccw(p3,p4,p2);
    if(((orientation1 > 0 && orientation2 < 0 ) || (orientation1 < 0 && orientation2 > 0))
        && ((orientation3 > 0 && orientation4 < 0) || (orientation3 < 0 && orientation4 > 0)))
        return true;
    else if(orientation1 == 0 && onSegment(p1,p2,p3)) return true;
    else if(orientation2 == 0 && onSegment(p1,p2,p4)) return true;
    else if(orientation3 == 0 && onSegment(p3,p4,p1)) return true;
    else if(orientation4 == 0 && onSegment(p3,p4,p2)) return true;
    else return false;
}

// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
class unionfind{
    std::vector<int> id;
    // std::std::vector<int> height;

public:
    unionfind(int n){
        id.resize(n);
        // height=std::vector<int> y(n,0);
        for(int i=0;i<n;i++){ // arreglar a codigo mas prolijo
            id[i]=i;
        }
    }
    bool connected(int a, int b){
        return id[a]==id[b];
    }

    int find(int i){
        return id[i];
    }

    void union_(int a, int b){
        int aID=find(a);
        int bID=find(b);

        if(connected(a,b)) return; // they're already connected

        for(int i=0;i<id.size();i++){
            if(id[i]==aID) id[i]=bID;
        }
    }

    void printid(){
        for(auto &elem : id) cout<<elem<<" ";
        cout<<"\n";
    }
};

// ======================================================

int main(){
    int t,n,m,ax,ay,bx,by,x,y;
    cin>>t;
    for(int i=0; i < t; i++){
        cin>>n>>m;
        unionfind uf(n);
        std::vector<point<int> > points;
        for(int j=0; j < n; j++){
            point<int> p, q;
            cin>>ax>>ay>>bx>>by;
            p=point<int>(ax,ay);
            q=point<int>(bx,by);
            points.push_back(p);
            points.push_back(q);
            if(j>0){
                int index=points.size()-1;
                int iaux=0, seg=j-1;
                for(int k = index-2;k >= 1;k-=2){
                    if(segmentsIntersect(points[index], points[index-1], points[k], points[k-1])){
                        uf.union_(j,seg);
                    }
                    seg--;
                }
            }

        }

        for(int j=0; j < m; j++){
            cin>>x>>y;
            if(uf.connected(x-1,y-1)){
                cout<<"YES\n";
            }else{
                cout<<"NO\n";
            }
        }
    }
}
