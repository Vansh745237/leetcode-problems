class Solution {
public:
    int m, n;
    vector<vector<bool>> vis;

    bool dfs(vector<vector<char>>& board, string& word,
             int i, int j, int k) {

        if (k == word.size())
            return true;

        if (i < 0 || j < 0 || i >= m || j >= n ||
            vis[i][j] || board[i][j] != word[k])
            return false;

        vis[i][j] = true;

        bool found = dfs(board, word, i + 1, j, k + 1) ||
                     dfs(board, word, i - 1, j, k + 1) ||
                     dfs(board, word, i, j + 1, k + 1) ||
                     dfs(board, word, i, j - 1, k + 1);

        vis[i][j] = false;

        return found;
    }

    bool exist(vector<vector<char>>& board, string word) {
        m = board.size();
        n = board[0].size();
        vis.assign(m, vector<bool>(n, false));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dfs(board, word, i, j, 0))
                    return true;
            }
        }

        return false;
    }
};