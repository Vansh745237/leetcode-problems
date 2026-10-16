
class Solution {
public:
    int sumCounts(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        int n = nums.size();

        vector<long long> sum(4 * n, 0);
        vector<long long> lazy(4 * n, 0);
        vector<long long> sq(4 * n, 0);

        auto push = [&](auto&& self, int node, int l, int r) -> void {
            if (lazy[node] == 0) return;

            long long v = lazy[node];
            long long len = r - l + 1;

            sq[node] = (sq[node] + 2 * v % MOD * sum[node] % MOD
                        + len % MOD * v % MOD * v % MOD) % MOD;

            sum[node] = (sum[node] + len * v) % MOD;

            if (l != r) {
                lazy[node * 2] = (lazy[node * 2] + v) % MOD;
                lazy[node * 2 + 1] = (lazy[node * 2 + 1] + v) % MOD;
            }

            lazy[node] = 0;
        };

        auto update = [&](auto&& self, int node, int l, int r,
                          int ql, int qr, long long val) -> void {
            push(push, node, l, r);

            if (r < ql || l > qr) return;

            if (ql <= l && r <= qr) {
                lazy[node] = val;
                push(push, node, l, r);
                return;
            }

            int mid = (l + r) / 2;
            self(self, node * 2, l, mid, ql, qr, val);
            self(self, node * 2 + 1, mid + 1, r, ql, qr, val);

            sum[node] = (sum[node * 2] + sum[node * 2 + 1]) % MOD;
            sq[node] = (sq[node * 2] + sq[node * 2 + 1]) % MOD;
        };

        unordered_map<int, int> last;
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int prev = last.count(nums[i]) ? last[nums[i]] : -1;

            update(update, 1, 0, n - 1, prev + 1, i, 1);

            last[nums[i]] = i;
            ans = (ans + sq[1]) % MOD;
        }

        return ans;
    }
};
