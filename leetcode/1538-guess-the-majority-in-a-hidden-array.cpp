/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * class ArrayReader {
 *   public:
 *     // Compares 4 different elements in the array
 *     // return 4 if the values of the 4 elements are the same (0 or 1).
 *     // return 2 if three elements have a value equal to 0 and one element has value equal to 1 or vice versa.
 *     // return 0 : if two element have a value equal to 0 and two elements have a value equal to 1.
 *     int query(int a, int b, int c, int d);
 *
 *     // Returns the length of the array
 *     int length();
 * };
 */

class Solution {
public:
    int guessMajority(ArrayReader &reader) {
        int n = reader.length(), m = 5;
        int f[5] = {
            -1,
            reader.query(0, 2, 3, 4),
            reader.query(0, 1, 3, 4),
            reader.query(0, 1, 2, 4),
            reader.query(0, 1, 2, 3),
        }, col[5] = {};
        int dt = 1;
        for(int i = 2; i < 5; ++i)
            if(f[1] != f[i]) {
                col[i] = 1;
                --dt;
            } else {
                ++dt;
            }
        if(abs(dt) != f[1])
            for(int i = 1; i < 5; ++i)
                col[i] = !col[i];
        int x = -1, y = -1, z = -1;
        for(int i = 0; x == -1 && i < 5; ++i)
            for(int j = i + 1; x == -1 && j < 5; ++j)
                if(col[i] == col[j]) {
                    x = i;
                    y = j;
                }
        dt = 0;
        for(int i = 0; i < 5; ++i) {
            // printf("col %d: %d\n", i, col[i]);
            if(col[i] != col[x]) {
                --dt;
                z = i;
            } else {
                ++dt;
            }
        }
        // printf("x %d y %d z %d dt %d\n", x, y, z, dt);
        if((n - m) & 1) {
            int col5 = f[4] == reader.query(1, 2, 3, 5) ? col[0] : !col[0];
            // printf("col 5: %d\n", col5);
            if(col5 != col[x]) {
                --dt;
                z = 5;
            } else {
                ++dt;
            }
            ++m;
        }
        for(int i = m; i < n; i += 2) {
            int res = reader.query(x, y, i, i + 1);
            // printf("res %d %d %d\n", i, i + 1, res);
            if(!res) {
                dt -= 2;
                z = i + 1;
            } else if(res == 4) {
                dt += 2;
            }
        }
        return !dt ? -1 : (dt > 0 ? x : z);
    }
};
