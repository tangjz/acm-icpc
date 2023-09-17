/**
 * Definition for a street.
 * class Street {
 * public:
 *     Street(vector<int> doors);
 *     void openDoor();
 *     void closeDoor();
 *     bool isDoorOpen();
 *     void moveRight();
 *     void moveLeft();
 * };
 */
class Solution {
public:
    int houseCount(Street* street, int k) {
        int ans = 0;
        if(!street -> isDoorOpen())
            street -> openDoor();
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
