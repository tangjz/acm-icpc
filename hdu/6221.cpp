#include <bits/stdc++.h>
typedef long long LL;
const int maxr = 5, maxc = 4, maxd = 13, maxs = 1 << maxd;
const char Figure[] = "23456789TJQKA", Suit[] = "dchs";
const char *Hand[] = {"High Card", "1 Pair", "2 Pairs", "3 of a Kind", "Straight", "Flush", "Full House", "4 of a Kind", "Straight Flush"};
int t, bits[maxs | 1], Log[maxs | 1], top = -1, stk[maxr][maxd + 2];
std::unordered_map<LL, int> Hash[maxr + 2];
inline int nextComb(int mask) {
    int lbt = mask & -mask, upp = mask + lbt;
    return upp | (mask & ~upp) >> (Log[lbt] + 1);
}
inline LL min_rep(LL mask) {
    for(int i = 0; i < 52; i += 4) {
        int pre = (mask >> i) & 15, cur = (1 << bits[pre]) - 1;
        mask ^= (LL)(pre ^ cur) << i;
    }
    return mask;
}
int dfs(LL mask, int rem, int upp) {
    if(!rem)
        return 0;
    if(Hash[rem].count(mask))
        return Hash[rem][mask];
    int ret = 0, sft = (rem - 1) << 2;
    if(upp == 8) { // Straight Flush
        for(int i = 0; i < 4; ++i) {
            int cnt = (mask >> (i + 48)) & 1; // Ax
            for(int j = i; j < 52; j += 4)
                if(!((mask >> j) & 1))
                    cnt = 0;
                else if((++cnt) >= 5)
                    ret = std::max(ret, 8 << sft | dfs(mask ^ (j >= 16 ? 69905LL << (j - 16) : 281474976715025LL << i), rem - 1, upp));
        }
        if(ret)
            return Hash[rem][mask] = ret;
        upp = 7;
    } // else, each suit has at most 11 cards
    if(upp == 7) { // 4 of a Kind: 4 same figure + 1 unnecessary
        for(int i = 0; i < 52; i += 4)
            if(((mask >> i) & 15) == 15)
                ret = std::max(ret, 7 << sft | dfs(mask ^ (15LL << i), rem - 1, upp));
        if(ret)
            return Hash[rem][mask] = ret;
        upp = 6;
    } // else, each figure has at most 3 cards
    if(upp == 6) { // Full House
        for(int i = 0; i < 52; i += 4) {
            int three = (mask >> i) & 15;
            if(bits[three] < 3)
                continue;
            LL nmsk = mask ^ ((LL)three << i);
            for(int j = 0; j < 52; j += 4) {
                int two = (nmsk >> j) & 15;
                if(bits[two] == 3) { // 3 choose 2
                    for(int k = 0; k < 4; ++k)
                        if((two >> k) & 1)
                            ret = std::max(ret, 6 << sft | dfs(nmsk ^ ((LL)(two ^ (1 << k)) << j), rem - 1, upp));
                } else if(bits[two] == 2) {
                    ret = std::max(ret, 6 << sft | dfs(nmsk ^ ((LL)two << j), rem - 1, upp));
                }
            }
        }
        if(ret)
            return Hash[rem][mask] = ret;
        upp = 5;
    }
    if(upp == 5) { // Flush: 5 cards or 10 cards
        for(int i = 0; i < 4; ++i) {
            int &ctr = (stk[++top][0] = 0);
            for(int j = i; j < 52; j += 4)
                if((mask >> j) & 1)
                    stk[top][++stk[top][0]] = j;
            if(ctr >= 5) {
                int dt = ctr / 5, adt = dt == 1 ? 5 << sft : 85 << (sft - 4);
                for(int j = (1 << (dt * 5)) - 1; j < 1 << ctr; j = nextComb(j)) {
                    LL sel = 0;
                    for(int k = j, lbt; k; k ^= lbt) {
                        lbt = k & -k;
                        sel |= 1LL << stk[top][Log[lbt] + 1];
                    }
                    ret = std::max(ret, adt | dfs(mask ^ sel, rem - dt, upp));
                }
            }
            --top;
        }
        if(ret)
            return Hash[rem][mask] = ret;
        upp = 4;
    } // else, suit is unnecessary
    mask = min_rep(mask);
    if(Hash[rem].count(mask))
        return Hash[rem][mask];
    if(upp == 4) { // Straight
        int cnt = (mask >> 48) & 1; // A
        for(int i = 0; i < 52; i += 4)
            if(!((mask >> i) & 1))
                cnt = 0;
            else if((++cnt) >= 5)
                ret = std::max(ret, 4 << sft | dfs(mask ^ (i >= 16 ? 69905LL << (i - 16) : 281474976715025LL), rem - 1, upp));
        if(ret)
            return Hash[rem][mask] = ret;
    } // else, figure is unnecessary
    static int ctr[maxc | 1];
    ctr[2] = ctr[3] = 0;
    for(int i = 0; i < 52; i += 4)
        ++ctr[bits[(mask >> i) & 15]];
    // 3 of a Kind, 2 Pairs, 1 Pair, High Card
    for( ; sft >= 0 && ctr[3]; sft -= 4) {
        --ctr[3];
        ret |= 3 << sft;
    }
    for( ; sft >= 0 && ctr[2]; sft -= 4) {
        int typ = std::min(ctr[2], 2);
        ctr[2] -= typ;
        ret |= typ << sft;
    }
    return Hash[rem][mask] = ret;
}
int solve() {
    LL mask = 0;
    for(int i = 0; i < 25; ++i) {
        LL tp = -1;
        char buf[3];
        scanf("%s", buf);
        for(int j = 0; tp == -1; ++j)
            if(buf[0] == Figure[j])
                for(int k = 0; tp == -1; ++k)
                    if(buf[1] == Suit[k])
                        tp = j << 2 | k;
        mask |= 1LL << tp;
    }
    for(int i = 1; i <= maxr; ++i)
        std::unordered_map<LL, int>().swap(Hash[i]);
    return dfs(mask, maxr, 8);
}
int main() {
    Log[0] = -1;
    for(int i = 1; i < maxs; ++i) {
        Log[i] = Log[i >> 1] + 1;
        bits[i] = bits[i >> 1] + (i & 1);
    }
    scanf("%d", &t);
    while(t--) {
        int fir = solve(), sec = solve(), stp = 5;
        if(fir == sec) {
            printf("Tie");
        } else {
            printf("Player %d", fir < sec ? 2 : 1);
            for( ; (fir >> 4) != (sec >> 4); fir >>= 4, sec >>= 4, --stp);
            if(fir < sec)
                std::swap(fir, sec);
        }
        while(stp--)
            printf(", %s", Hand[(fir >> (stp << 2)) & 15]);
        putchar('\n');
    }
    return 0;
}