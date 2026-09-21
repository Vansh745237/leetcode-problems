class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k, 0);
        
        vector<long long> dp(k, 0), next(k, 0);
        
        for (int num : nums) {
            int r = num % k;
            
            next.assign(k, 0);
            next[r]++;
            
            for (int j = 0; j < k; j++) {
                if (dp[j] > 0) {
                    next[(j * r) % k] += dp[j];
                }
            }
            
            dp = next;
            
            for (int j = 0; j < k; j++) {
                ans[j] += dp[j];
            }
        }
        
        return ans;
    }
};
