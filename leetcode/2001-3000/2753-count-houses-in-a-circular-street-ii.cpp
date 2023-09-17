/**
 * Definition for a street.
 * class Street {
 * public:
 *     Street(vector<int> doors);
 *     void closeDoor();
 *     bool isDoorOpen();
 *     void moveRight();
 * };
 */
class Solution {
public:
    int houseCount(Street* street, int k) {
        int ans = 0;
        for( ; !street -> isDoorOpen(); street -> moveRight());
        for(int i = 1; i <= k; ++i) {
            street -> moveRight();
            if(street -> isDoorOpen()) {
                ans = i;
                street -> closeDoor();
            }
        }
        return ans;
    }
};
