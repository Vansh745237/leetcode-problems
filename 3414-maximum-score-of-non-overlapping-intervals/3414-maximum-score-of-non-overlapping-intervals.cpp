class Solution {
public:
    using ll = long long;

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // Store: {left, right, weight, original_index}
        vector<array<ll, 4>> a;

        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        // Sort by left endpoint
        sort(a.begin(), a.end(), [](auto &x, auto &y) {
            if (x[0] != y[0])
                return x[0] < y[0];
            return x[1] < y[1];
        });

        // next[i] = first interval whose left > a[i].right
        vector<int> next(n);

        vector<ll> starts(n);
        for (int i = 0; i < n; i++)
            starts[i] = a[i][0];

        for (int i = 0; i < n; i++) {
            next[i] =
                upper_bound(starts.begin(), starts.end(), a[i][1])
                - starts.begin();
        }

        /*
            dp[i][k] = best answer using intervals from i onward,
                       choosing at most k intervals.

            We store:
              score
              vector of original indices
        */

        struct Node {
            ll score = 0;
            vector<int> ids;
        };

        vector<vector<Node>> dp(n + 1, vector<Node>(5));

        auto better = [](const Node &A, const Node &B) {
            if (A.score != B.score)
                return A.score > B.score;

            // Lexicographically smaller index vector wins
            return A.ids < B.ids;
        };

        for (int i = n - 1; i >= 0; i--) {

            for (int k = 0; k <= 4; k++) {

                // Option 1: skip current interval
                dp[i][k] = dp[i + 1][k];

                // Option 2: take current interval
                if (k > 0) {
                    Node take = dp[next[i]][k - 1];

                    take.score += a[i][2];
                    take.ids.push_back((int)a[i][3]);

                    // We need sorted original indices for lexicographic comparison
                    sort(take.ids.begin(), take.ids.end());

                    if (better(take, dp[i][k]))
                        dp[i][k] = take;
                }
            }
        }

        return dp[0][4].ids;
    }
};