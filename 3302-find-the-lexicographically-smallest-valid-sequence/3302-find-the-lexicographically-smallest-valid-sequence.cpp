class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // next[i] = maximum number of characters of word2
        // that can be matched starting from word1[i]
        vector<int> next(n + 1, 0);

        int j = m - 1;
        for (int i = n - 1; i >= 0; i--) {
            if (j >= 0 && word1[i] == word2[j]) {
                j--;
            }
            next[i] = m - 1 - j;
        }

        vector<int> ans;
        int pos = 0;
        bool changed = false;

        for (int i = 0; i < m; i++) {
            // Try exact match first
            while (pos < n && word1[pos] != word2[i]) {
                // We can change this character if we haven't used
                // our one allowed modification.
                if (!changed && pos + 1 <= n &&
                    next[pos + 1] >= m - i - 1) {
                    ans.push_back(pos);
                    changed = true;
                    pos++;
                    break;
                }
                pos++;
            }

            if (ans.size() == i + 1) {
                continue;
            }

            if (pos >= n) {
                return {};
            }

            ans.push_back(pos);
            pos++;
        }

        return ans;
    }
};