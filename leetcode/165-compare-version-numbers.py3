class Solution:
    def compareVersion(self, version1: str, version2: str) -> int:
        p = list(map(int, version1.split(".")))
        q = list(map(int, version2.split(".")))
        dt = len(p) - len(q)
        if dt < 0:
            p += [0] * -dt
        if dt > 0:
            q += [0] * dt
        sgn = 0
        if p > q:
            sgn += 1
        if p < q:
            sgn -= 1
        return sgn
