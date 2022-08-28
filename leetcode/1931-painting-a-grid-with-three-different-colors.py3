class Solution:
    def colorTheGrid(self, m: int, n: int) -> int:
        mod = 10 ** 9 + 7
        row = [[i] for i in range(3)]
        for i in range(1, m):
            nxt = []
            for seq in row:
                for j in range(3):
                    if seq[-1] != j:
                        nxt += [seq + [j]]
            row = nxt
        tr = [[1 if all(row[i][k] != row[j][k] for k in range(m)) else 0 for j in range(len(row))] for i in range(len(row))]
        dp = [1 for i in range(len(row))]
        for i in range(1, n):
            dp = [sum(tr[j][k] * dp[k] for k in range(len(row))) % mod for j in range(len(row))]
        return sum(dp) % mod
