/**
 * // This is the robot's control interface.
 * // You should not implement it, or speculate about its implementation
 * class Robot {
 *   public:
 *     // Returns true if the cell in front is open and robot moves into the cell.
 *     // Returns false if the cell in front is blocked and robot stays in the current cell.
 *     bool move();
 *
 *     // Robot will stay in the same cell after calling turnLeft/turnRight.
 *     // Each turn will be 90 degrees.
 *     void turnLeft();
 *     void turnRight();
 *
 *     // Clean the current cell.
 *     void clean();
 * };
 */

class Solution {
    static const int maxd = 4;
    static constexpr int dx[maxd] = {-1, 0, 1, 0}, dy[maxd] = {0, 1, 0, -1};
    
    void dfs(int x, int y, Robot &bot, int &d, set<pair<int, int> > &sp) {
        int r = (d + 2) % maxd;
        bot.clean();
        for(int i = 0; i < maxd; ++i) {
            int xx = x + dx[d], yy = y + dy[d];
            if(sp.insert({xx, yy}).second && bot.move()) {
                dfs(xx, yy, bot, d, sp);
                bot.turnLeft();
                (--d) < 0 && (d += maxd);
            } else {
                bot.turnRight();
                (++d) == maxd && (d = 0);
            }
        }
        for( ; d != r; (++d) == maxd && (d = 0))
            bot.turnRight();
        bot.move();
    }
public:
    void cleanRoom(Robot& robot) {
        int d = 0;
        set<pair<int, int> > sp;
        sp.insert({0, 0});
        dfs(0, 0, robot, d, sp);
    }
};
