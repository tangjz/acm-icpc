class Solution:
    def composeCube(self, shapes: List[List[str]]) -> bool:
        n = len(shapes[0])
        if sum(sum(row.count('1') for row in shape) for shape in shapes) != 6 * n * n - 12 * n + 8:
            return False
        def gen(shape):
            ret = [0] * 48
            for i in range(n):
                for j in range(n):
                    if shape[i][j] == '0': continue
                    for c0, (p, q) in enumerate(((i, j), (i, n - 1 - j))):
                        for c1, (u, v) in enumerate(((p, q), (q, n - 1 - p), (n - 1 - p, n - 1 - q), (n - 1 - q, p))):
                            for c2, (x, y, z) in enumerate(((u, v, 0), (u, v, n - 1), (u, 0, v), (u, n - 1, v), (0, u, v), (n - 1, u, v))):
                                ret[(c2 << 2 | c1) << 1 | c0] |= 1 << ((x * n + y) * n + z)
            return ret
        
        cur = set(gen(shapes[0])[:1])
        for shape in shapes[1:]:
            cur = {u | v for u in set(gen(shape)) for v in cur if not (u & v)}
        return len(cur) > 0
