#include<vector>
#include<iostream>
using namespace std;

class Solution {
private:
    struct DisjointNode {
        DisjointNode* next = NULL;
        char type = '0';
    };

    vector<vector<char>> grid;
    vector<vector<DisjointNode>> disjoint;
    int rows, cols;

    DisjointNode* getDisjointNode(int x, int y) {
        if (x < 0 || x >= rows) return NULL;
        if (y < 0 || y >= cols) return NULL;

        return &(this->disjoint[x][y]);
    }

    DisjointNode* getDisjointParent(DisjointNode* node) {
        if (!node) return NULL;

        DisjointNode* cur = node;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        
        return cur;
    }

    DisjointNode* getDisjointParent(int x, int y) {
        return getDisjointParent(getDisjointNode(x, y));
    }

    void connect() {
        for (int x = 0; x < this->rows; x++) {
            for (int y = 0; y < this->cols; y++) {
                DisjointNode* cur = &this->disjoint[x][y];
                cur->type = this->grid[x][y];

                if (cur->type == '0') continue;
                DisjointNode* above = getDisjointParent(x - 1, y);
                DisjointNode* left = getDisjointParent(x, y - 1);

                if (above && above->type == '1') {
                    cur->next = above;
                    if (left && left->type == '1' && left != above) {
                        left->next = above;
                    }
                } else if (left && left->type == '1') {
                    cur->next = left;
                }
            }
        }
    }

public:
    int numIslands(vector<vector<char>>& grid) {
        this->rows = grid.size();
        this->cols = (rows > 0) ? grid[0].size() : 0;

        this->grid = grid;
        this->disjoint = vector<vector<DisjointNode>>(this->rows, std::vector<DisjointNode>(this->cols, DisjointNode()));
        connect();

        int count = 0;
        for (auto row : disjoint) {
            for (auto node : row) {
                if (node.next == NULL && node.type == '1') count++;
            }
        }

        return count;
    }
};

int main() {
    vector<vector<char>> grid = {
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','1'},
        {'0','0','0','1','0'}
    };

    Solution sol = Solution();
    cout << sol.numIslands(grid) << endl;
}
