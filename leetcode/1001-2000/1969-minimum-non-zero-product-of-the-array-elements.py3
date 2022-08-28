class Solution:
    def minNonZeroProduct(self, p: int) -> int:
        mod = 10 ** 9 + 7
        n = 1 << p
        m = pow(n - 2, (n >> 1) - 1, mod) if n > 2 else 1
        return m * (n - 1) % mod
