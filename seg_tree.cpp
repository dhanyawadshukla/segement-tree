#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
    vector<int> tree;
    int n;
    
public:
    SegmentTree(vector<int>& data) {
        n = data.size();
        tree.resize(4 * n);
        build(data, 0, n - 1, 1);
    }
    
    void build(vector<int>& data, int start, int end, int node) {
        if (start == end) {
            tree[node] = data[start];
        } else {
            int mid = (start + end) / 2;
            build(data, start, mid, 2 * node);
            build(data, mid + 1, end, 2 * node + 1);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }
    
    int query(int L, int R, int start, int end, int node) {
        if (R < start || L > end) return 0;
        if (L <= start && end <= R) return tree[node];
        
        int mid = (start + end) / 2;
        return query(L, R, start, mid, 2 * node) + query(L, R, mid + 1, end, 2 * node + 1);
    }
    
    void update(int index, int value, int start, int end, int node) {
        if (start == end) {
            tree[node] = value;
        } else {
            int mid = (start + end) / 2;
            if (index <= mid) {
                update(index, value, start, mid, 2 * node);
            } else {
                update(index, value, mid + 1, end, 2 * node + 1);
            }
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }
    
    int query(int L, int R) {
        return query(L, R, 0, n - 1, 1);
    }
    
    void update(int index, int value) {
        update(index, value, 0, n - 1, 1);
    }
};

int main() {
    vector<int> data = {1, 3, 5, 7, 9, 11};
    SegmentTree segTree(data);
    
    cout << "Sum of values in given range = " << segTree.query(1, 3) << endl;
    
    segTree.update(1, 10);
    
    cout << "Updated sum of values in given range = " << segTree.query(1, 3) << endl;
    
    return 0;
}
