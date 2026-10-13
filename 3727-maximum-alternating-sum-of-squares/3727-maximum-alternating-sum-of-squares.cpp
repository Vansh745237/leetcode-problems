
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        vector<long long> a;

        for (int i = 0; i < nums.size(); i++) {
            long long x = nums[i];
            a.push_back(x * x);
        }

        sort(a.begin(), a.end());

        long long ans = 0;
        int n = a.size();

        for (int i = 0; i < n; i++) {
            if (i < (n + 1) / 2) {
                ans += a[n - 1 - i];
            } else {
                ans -= a[n - 1 - i];
            }
        }

        return ans;
    }
};
