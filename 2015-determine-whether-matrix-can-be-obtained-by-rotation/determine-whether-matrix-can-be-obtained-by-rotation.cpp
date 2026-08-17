class Solution {
public:
    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        int n = mat.size();

        for (int r = 0; r < 4; r++) {
            bool same = true;

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (mat[i][j] != target[i][j]) {
                        same = false;
                        break;
                    }
                }
            }

            if (same) return true;

            // Rotate 90° clockwise
            vector<vector<int>> temp(n, vector<int>(n));

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    temp[j][n - 1 - i] = mat[i][j];
                }
            }

            mat = temp;
        }

        return false;
    }
};