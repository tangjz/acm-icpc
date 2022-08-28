/**
 * // This is the FontInfo's API interface.
 * // You should not implement it, or speculate about its implementation
 * class FontInfo {
 *   public:
 *     // Return the width of char ch when fontSize is used.
 *     int getWidth(int fontSize, char ch);
 *     
 *     // Return Height of any char when fontSize is used.
 *     int getHeight(int fontSize)
 * };
 */
class Solution {
public:
    int maxFont(string text, int w, int h, vector<int>& fonts, FontInfo fontInfo) {
        int L = -1, R = fonts.size() - 1;
        while(L < R) {
            int M = (L + R + 1) >> 1;
            int val = fontInfo.getHeight(fonts[M]);
            // printf("height %d (%d): %d\n", fonts[M], M, val);
            if(val > h) {
                R = M - 1;
            } else {
                L = M;
            }
        }
        if(L == -1)
            return -1;
        R = L;
        L = -1;
        while(L < R) {
            int M = (L + R + 1) >> 1;
            int rem = w;
            for(char ch: text) {
                int val = fontInfo.getWidth(fonts[M], ch);
                // printf("width %d %c (%d): %d\n", fonts[M], ch, M, val);
                rem -= val;
                if(rem < 0)
                    break;
            }
            if(rem < 0) {
                R = M - 1;
            } else {
                L = M;
            }
        }
        return L == -1 ? -1 : fonts[L];
    }
};
