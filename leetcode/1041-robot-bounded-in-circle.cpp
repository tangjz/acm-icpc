class Solution {
public:
    bool isRobotBounded(string seq) {
        seq += seq;
        seq += seq;
        const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
        int x = 0, y = 0, o = 0;
        for(char ch: seq) {
            if(ch == 'G') {
                x += dx[o];
                y += dy[o];
            } else {
                (o += ch == 'R' ? 1 : 3) >= 4 && (o -= 4);
            }
        }
        return !x && !y;
    }
};
