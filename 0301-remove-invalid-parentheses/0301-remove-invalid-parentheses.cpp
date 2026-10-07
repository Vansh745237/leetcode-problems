class Solution {
public:
    vector<string> ans;

    void removeInvalid(string s, int start, int lremove, int rremove) {
        // If removals are finished, check validity
        if (lremove == 0 && rremove == 0) {
            int balance = 0;

            for (char c : s) {
                if (c == '(') balance++;
                else if (c == ')') {
                    balance--;
                    if (balance < 0) return;
                }
            }

            if (balance == 0)
                ans.push_back(s);

            return;
        }

        for (int i = start; i < s.size(); i++) {

            // Avoid removing duplicate parentheses
            if (i > start && s[i] == s[i - 1])
                continue;

            // We only remove parentheses
            if (s[i] != '(' && s[i] != ')')
                continue;

            // Remove '('
            if (lremove > 0 && s[i] == '(') {
                string temp = s.substr(0, i) + s.substr(i + 1);
                removeInvalid(temp, i, lremove - 1, rremove);
            }

            // Remove ')'
            if (rremove > 0 && s[i] == ')') {
                string temp = s.substr(0, i) + s.substr(i + 1);
                removeInvalid(temp, i, lremove, rremove - 1);
            }
        }
    }

    vector<string> removeInvalidParentheses(string s) {

        int lremove = 0, rremove = 0;

        // Find minimum number of '(' and ')' to remove
        for (char c : s) {
            if (c == '(') {
                lremove++;
            }
            else if (c == ')') {
                if (lremove > 0)
                    lremove--;
                else
                    rremove++;
            }
        }

        removeInvalid(s, 0, lremove, rremove);

        return ans;
    }
};