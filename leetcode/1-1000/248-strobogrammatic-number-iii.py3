class Solution:
    def strobogrammaticInRange(self, low: str, high: str) -> int:
        upp = len(high)
        low, high = map(int, (low, high,))
        cand = (0, 1, 6, 8, 9,)
        que = [""] + [str(x) for x in cand if x not in (6, 9,) and x <= high]
        vis = set(que)
        while len(que) > 0:
            buf = que[-1]
            que = que[:-1]
            for x in cand:
                y = x if x not in (6, 9,) else 15 - x
                nxt = str(x) + buf + str(y)
                if len(nxt) <= upp and int(nxt) <= high and nxt not in vis:
                    vis.add(nxt)
                    que += [nxt]
        vis = {int(x) for x in vis if x and (x[0] != '0' or x == '0') and int(x) >= low}
        return len(vis)
