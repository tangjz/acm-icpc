const int maxn = 23, maxd = 7, maxv = (int)1.8e5;
int ans, boardsLen[maxd], handsLen[maxd], ordsLen[maxd], ords[maxd][maxn];
char boards[maxd][maxn], hands[maxd][maxn];
long long ctr;
void dfs(int dep) {
    if((++ctr) >= maxv)
        return;
    int &bLen = boardsLen[dep], &hLen = handsLen[dep];
    char *board = boards[dep], *hand = hands[dep];
    if(!bLen) {
        ans = dep;
        return;
    }
    if(dep + 1 >= ans || !hLen)
        return;
    for(int i = 0; i < hLen; ++i) {
        if(i && hand[i - 1] == hand[i])
            continue;
        int bestPlace = -1;
        int &oLen = ordsLen[dep] = 0, *ord = ords[dep];
        for(int j = 0; j <= bLen; ++j) {
            if(j && board[j - 1] == hand[i])
                continue;
            ord[oLen++] = j;
            if(j < bLen && board[j] == hand[i])
                bestPlace = oLen - 1;
        }
        if(bestPlace != -1)
            rotate(ord, ord + bestPlace, ord + oLen);

        for(int jd = 0; jd < oLen; ++jd) {
            int j = ord[jd];
            int &nLen = boardsLen[dep + 1] = bLen + 1, &rLen = handsLen[dep + 1] = hLen - 1;
            char *nxt = boards[dep + 1], *rem = hands[dep + 1];
            memcpy(rem, hand, i * sizeof(char));
            memcpy(rem + i, hand + i + 1, (rLen - i) * sizeof(char));
            memcpy(nxt, board, j * sizeof(char));
            nxt[j] = hand[i];
            memcpy(nxt + j + 1, board + j, (bLen - j) * sizeof(char));
            int L = j + 1, R = j - 1;
            while(L > 0 && R + 1 < nLen && nxt[L - 1] == nxt[R + 1]) {
                int cnt = 0, nL = L, nR = R;
                char ch = nxt[L - 1];
                if(nL - 2 == nR)
                    ++nR;
                for( ; nL > 0 && nxt[nL - 1] == ch; --nL, ++cnt);
                for( ; nR + 1 < nLen && nxt[nR + 1] == ch; ++nR, ++cnt);
                if(cnt < 3)
                    break;
                L = nL;
                R = nR;
            }
            if(L <= R) {
                memmove(nxt + L, nxt + R + 1, (nLen - 1 - R) * sizeof(char));
                nLen -= R - L + 1;
            }
            dfs(dep + 1);
        }
    }
}

class Solution {
public:
    int findMinStep(string board, string hand) {
        int &bLen = boardsLen[0] = board.size(), &hLen = handsLen[0] = hand.size();
        char *b = boards[0], *h = hands[0];
        for(int i = 0; i < bLen; ++i)
            b[i] = board[i];
        for(int i = 0; i < hLen; ++i)
            h[i] = hand[i];
        sort(h, h + hLen);
        ans = hLen + 1;
        ctr = 0;
        dfs(0);
        return ans <= hLen ? ans : -1;
    }
};
