class Solution {
public:
    void solve(int index, int target, vector<int>& candidates,
               vector<int>& current, vector<vector<int>>& ans) {

        if (target == 0) {
            ans.push_back(current);
            return;
        }

        if (index == candidates.size() || target < 0)
            return;

      
        if (candidates[index] <= target) {
            current.push_back(candidates[index]);

            solve(index, target - candidates[index],
                  candidates, current, ans);

            current.pop_back();
        }

        // Skip current element
        solve(index + 1, target, candidates, current, ans);
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> current;

        solve(0, target, candidates, current, ans);

        return ans;
    }
};