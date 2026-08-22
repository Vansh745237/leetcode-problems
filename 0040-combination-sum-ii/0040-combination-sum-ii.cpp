class Solution {
public:
    void solve(int start, int target, vector<int>& candidates,
               vector<int>& current, vector<vector<int>>& ans) {

        if (target == 0) {
            ans.push_back(current);
            return;
        }

        for (int i = start; i < candidates.size(); i++) {

        
            if (i > start && candidates[i] == candidates[i - 1])
                continue;

            
            if (candidates[i] > target)
                break;

            current.push_back(candidates[i]);
            solve(i + 1, target - candidates[i],
                  candidates, current, ans);

            current.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {

        sort(candidates.begin(), candidates.end());

        vector<vector<int>> ans;
        vector<int> current;

        solve(0, target, candidates, current, ans);

        return ans;
    }
};