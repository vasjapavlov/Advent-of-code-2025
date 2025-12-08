#ifndef UnionFind_h
#define UnionFind_h
#import <vector>
using namespace std;
// https://github.com/vasjapavlov/MyAlgorithms/blob/master/UnionFind.cpp
struct Island {
    int root, size;
    Island(int _root, int _size) {
        root = _root;
        size = _size;
    }
    bool operator <(const Island &island) const {
        return root > island.root;
    }
};

class UnionFind {
private:
    vector<int> id;
    vector<int> sz;
    int getRoot(int node) {
        while(id[node] != node) {
            id[node] = id[ id[node] ];
            node = id[node];
        }
        return node;
    }
    
public:
    vector<int> getIslandSizes() {
        set<Island> islands;
        for(auto x : id) {
            int root = getRoot(x);
            islands.insert(Island(root, sz[root]));
        }
        
        vector<int> sizes;
        for (const auto& island : islands) {
            sizes.push_back(island.size);
        }
        sort(sizes.rbegin(), sizes.rend());
        return sizes;
    }

    UnionFind(int N) {
        id = vector<int>(N);
        sz = vector<int>(N);
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
        if(root1 == root2) {
            return sz[root1];
        }
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
