class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        vector<int> cnt(26);

        for (char c : s)
            cnt[c - 'a']++;

        int odd = -1;

        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2) {
                if (odd != -1)
                    return "";
                odd = i;
            }
        }

        vector<int> half(26);

        for (int i = 0; i < 26; i++)
            half[i] = cnt[i] / 2;

        int m = n / 2;
        string t = target.substr(0, m);

        vector<int> rem = half;
        bool possible = true;

        for (char c : t) {
            int x = c - 'a';

            if (rem[x] == 0) {
                possible = false;
                break;
            }

            rem[x]--;
        }

        if (possible) {
            string left = t;
            string ans = left;

            if (n % 2)
                ans += char('a' + odd);

            reverse(left.begin(), left.end());
            ans += left;

            if (ans > target)
                return ans;
        }

        for (int pos = m - 1; pos >= 0; pos--) {
            rem = half;
            bool ok = true;

            for (int j = 0; j < pos; j++) {
                int x = t[j] - 'a';

                if (rem[x] == 0) {
                    ok = false;
                    break;
                }

                rem[x]--;
            }

            if (!ok)
                continue;

            int chosen = -1;

            for (int c = t[pos] - 'a' + 1; c < 26; c++) {
                if (rem[c] > 0) {
                    chosen = c;
                    break;
                }
            }

            if (chosen == -1)
                continue;

            string left = t.substr(0, pos);
            left += char('a' + chosen);
            rem[chosen]--;

            for (int c = 0; c < 26; c++) {
                while (rem[c] > 0) {
                    left += char('a' + c);
                    rem[c]--;
                }
            }

            string ans = left;

            if (n % 2)
                ans += char('a' + odd);

            reverse(left.begin(), left.end());
            ans += left;

            return ans;
        }

        return "";
    }
};