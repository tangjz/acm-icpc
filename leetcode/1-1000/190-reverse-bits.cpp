class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        static const int SFT[] = {16, 8, 4, 2, 1};
        static const uint32_t HI[] = {0xFFFF0000, 0xFF00FF00, 0xF0F0F0F0, 0xCCCCCCCC, 0xAAAAAAAA};
        static const uint32_t LO[] = {0x0000FFFF, 0x00FF00FF, 0x0F0F0F0F, 0x33333333, 0x55555555};
        n = (n >> 16) | (n << 16);
        n = ((n & HI[1]) >> SFT[1]) | ((n & LO[1]) << SFT[1]);
        n = ((n & HI[2]) >> SFT[2]) | ((n & LO[2]) << SFT[2]);
        n = ((n & HI[3]) >> SFT[3]) | ((n & LO[3]) << SFT[3]);
        n = ((n & HI[4]) >> SFT[4]) | ((n & LO[4]) << SFT[4]);
        return n;
    }
};
