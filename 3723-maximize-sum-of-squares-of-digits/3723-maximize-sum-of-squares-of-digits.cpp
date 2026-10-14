
class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if (sum > num * 9) {
            return "";
        }

        string ans = "";

        while (num > 0) {
            if (sum >= 9) {
                ans += '9';
                sum -= 9;
            } else {
                ans += char('0' + sum);
                sum = 0;
            }

            num--;
        }

        if (sum > 0) {
            return "";
        }

        return ans;
    }
};

