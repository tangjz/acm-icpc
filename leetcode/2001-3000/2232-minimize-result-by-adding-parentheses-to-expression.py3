class Solution:
    def minimizeResult(self, pat: str) -> str:
        pos = pat.find('+')
        lft, rht = pat[:pos], pat[pos+1:]
        ans = int(lft) + int(rht)
        out = "(" + pat + ")"
        n, m = len(lft), len(rht)
        for i in range(n):
            for j in range(m):
                tmp = int(lft[i:]) + int(rht[:m-j])
                if i > 0:
                    tmp *= int(lft[:i])
                if j > 0:
                    tmp *= int(rht[m-j:])
                if tmp < ans:
                    ans = tmp
                    out = lft[:i] + "(" + lft[i:] + "+" + rht[:m-j] + ")" + rht[m-j:]
        return out
