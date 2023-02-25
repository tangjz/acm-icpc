class Solution {
public:
    string categorizeBox(int L, int W, int H, int M) {
        bool isB = max(L, max(W, H)) >= (int)1e4 || ((int)1e9 - 1) / L / W / H == 0;
        bool isH = M >= 100;
        return isB && isH ? "Both" : (isB ? "Bulky" : (isH ? "Heavy" : "Neither"));
    }
};
