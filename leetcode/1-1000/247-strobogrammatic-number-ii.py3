class Solution:
    def findStrobogrammatic(self, n: int) -> List[str]:
        cand = (0, 1, 6, 8, 9,)
        if n % 2 == 1:
            f = [str(x) for x in cand if x not in (6, 9,)]
        else:
            f = [""]
        cand = tuple((str(x), str(15 - x if x in (6, 9,) else x)) for x in cand)
        while len(f[0]) < n:
            g = []
            for pre in f:
                for x, y in cand:
                    g.append(x + pre + y)
            f = g
        return [x for x in f if x[0] != '0' or x == '0']
