class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        return rec1[0] < rec2[2] &&   // rec1 left < rec2 right
               rec1[2] > rec2[0] &&   // rec1 right > rec2 left
               rec1[1] < rec2[3] &&   // rec1 bottom < rec2 top
               rec1[3] > rec2[1];     // rec1 top > rec2 bottom
    }
};