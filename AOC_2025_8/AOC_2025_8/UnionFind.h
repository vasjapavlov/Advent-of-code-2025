#ifndef UnionFind_h
#define UnionFind_h

// https://github.com/vasjapavlov/MyAlgorithms/blob/master/UnionFind.cpp
class UnionFind {
private:
    int id[10000];
    int sz[10000];
    int getRoot(int node) {
        while(id[node] != node) {
            id[node] = id[ id[node] ];
            node = id[node];
        }
        return node;
    }
    
public:
    UnionFind(int N) {
        for(int i=0;i<N;i++) {
            id[i]=i;
            sz[i]=1;
        }
    }
    
    bool find(int nodeA, int nodeB) {
        return getRoot(nodeA) == getRoot(nodeB);
    }
    
    int unite(int nodeA,int nodeB) {
        int root1=getRoot(nodeA);
        int root2=getRoot(nodeB);
        
        if(sz[root1] < sz[root2]) {
            id[root1] = root2;
            sz[root2] += sz[root1];
            return sz[root2];
        }
        else {
            id[root2] = root1;
            sz[root1] += sz[root2];
            return sz[root1];
        }
    }
};

#endif /* UnionFind_h */
