class Solution:
    def splitString(self, s: str) -> bool:
        n = len(s)
        dp = []
        for i in range(n):
            cur = set()
            if i + 1 < n:
                cur.add(int(s[:i+1]))
            for j in range(i):
                val = int(s[j+1:i+1])
                if (val + 1) in dp[j]:
                    cur.add(val)
            dp.append(cur)
        return len(dp[-1]) > 0
