class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        unordered_set<int> s(nums.begin(), nums.end());

        for (int x = k; ; x += k) {
            if (s.find(x) == s.end()) {
                return x;
            }
        }
    }
};