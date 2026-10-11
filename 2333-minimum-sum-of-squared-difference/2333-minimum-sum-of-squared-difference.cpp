
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        long long k = (long long)k1 + k2;
        vector<int> diff(n);
        int maxi = 0;
        long long sum = 0;

        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            maxi = max(maxi, diff[i]);
            sum += diff[i];
        }

        if (k >= sum)
            return 0;

        int low = 0, high = maxi;

        while (low < high) {
            int mid = low + (high - low) / 2;
            long long need = 0;

            for (int i = 0; i < n; i++) {
                if (diff[i] > mid)
                    need += diff[i] - mid;
            }

            if (need <= k)
                high = mid;
            else
                low = mid + 1;
        }

        int level = low;
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            if (diff[i] > level) {
                k -= diff[i] - level;
                diff[i] = level;
            }
        }

        for (int i = 0; i < n; i++) {
            ans += 1LL * diff[i] * diff[i];
        }

        // Use remaining operations to reduce values at the boundary
        for (int i = 0; i < n && k > 0; i++) {
            if (diff[i] == level && level > 0) {
                ans -= 1LL * level * level;
                ans += 1LL * (level - 1) * (level - 1);
                k--;
                diff[i]--;
            }
        }

        return ans;
    }
};
