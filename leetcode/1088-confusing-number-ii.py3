class Solution:
    def confusingNumberII(self, n: int) -> int:
        buf = str(n + 1)
        upp = len(buf)
        ans = -1
        cand = (0, 1, 6, 8, 9,)
        for i in range(len(buf)):
            d = int(buf[i])
            for x in cand:
                if x >= d:
                    break
                ans += len(cand) ** (len(buf) - 1 - i)
            if d not in cand:
                break
        cand = (0, 1, 6, 8, 9,)
        que = [""] + [str(x) for x in cand if x not in (6, 9,) and x <= n]
        vis = set(que)
        while len(que) > 0:
            buf = que[-1]
            que = que[:-1]
            for x in cand:
                y = x if x not in (6, 9,) else 15 - x
                nxt = str(x) + buf + str(y)
                if len(nxt) <= upp and int(nxt) <= n and nxt not in vis:
                    vis.add(nxt)
                    que += [nxt]
        vis = {int(x) for x in vis if x and x[0] != '0'}
        return ans - len(vis)
