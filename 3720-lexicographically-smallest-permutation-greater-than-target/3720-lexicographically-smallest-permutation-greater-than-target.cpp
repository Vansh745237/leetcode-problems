class Solution {
public:
    string s, target;
    int n;
    
    string solve(int pos, vector<int>& cnt, bool greater) {
        if (pos == n) {
            return greater ? "" : "#";
        }

        if (greater) {
            string ans;
            for (int c = 0; c < 26; c++) {
                while (cnt[c] > 0) {
                    ans += char('a' + c);
                    cnt[c]--;
                }
            }
            return ans;
        }
        int x = target[pos] - 'a';

        if (cnt[x] > 0) {
            cnt[x]--;

            string suffix = solve(pos + 1, cnt, false);

            if (suffix != "#") {
                cnt[x]++;
                return char('a' + x) + suffix;
            }

            cnt[x]++;
        }
        for (int c = x + 1; c < 26; c++) {
            if (cnt[c] > 0) {
                cnt[c]--;

                string ans;
                ans += char('a' + c);
                for (int j = 0; j < 26; j++) {
                    while (cnt[j] > 0) {
                        ans += char('a' + j);
                        cnt[j]--;
                    }
                }

                return ans;
            }
        }

        return "#";
    }

    string lexGreaterPermutation(string s, string target) {
        this->s = s;
        this->target = target;
        n = s.size();

        vector<int> cnt(26, 0);

        for (char c : s)
            cnt[c - 'a']++;

        string ans = solve(0, cnt, false);

        return ans == "#" ? "" : ans;
    }
};