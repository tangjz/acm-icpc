class Solution {
public:
    int maxBoxesInWarehouse(vector<int>& boxes, vector<int>& warehouse) {
        sort(boxes.begin(), boxes.end());
        int ans = 0, L = 0, R = warehouse.size() - 1;
        while(!boxes.empty() && L <= R) {
            int x = boxes.back();
            boxes.pop_back();
            if(x <= warehouse[L]) {
                ++L;
                ++ans;
            } else if(x <= warehouse[R]) {
                --R;
                ++ans;
            }
        }
        return ans;
    }
};
