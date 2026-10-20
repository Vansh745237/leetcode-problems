
class Solution {
    bool isRotation(vector<int>& nums, vector<int>& sorted,
                    int start, int k) {
        vector<int> pi(k, 0);

        // Build KMP prefix array for the sorted block.
        for (int i = 1; i < k; i++) {
            int j = pi[i - 1];

            while (j > 0 && sorted[start + i] != sorted[start + j])
                j = pi[j - 1];

            if (sorted[start + i] == sorted[start + j])
                j++;

            pi[i] = j;
        }

        // Search the sorted block in the original block doubled.
        int j = 0;

        for (int i = 0; i < 2 * k - 1; i++) {
            int x = nums[start + (i % k)];

            while (j > 0 && x != sorted[start + j])
                j = pi[j - 1];

            if (x == sorted[start + j])
                j++;

            if (j == k)
                return true;
        }

        return false;
    }

public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();

        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());

        int ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0)
                continue;

            bool ok = true;

            for (int start = 0; start < n; start += k) {
                if (!isRotation(nums, sorted, start, k)) {
                    ok = false;
                    break;
                }
            }

            if (ok)
                ans += k;
        }

        return ans;
    }
};

