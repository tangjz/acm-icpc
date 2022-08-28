class Solution:
    def isBalanced(self, n: int) -> bool:
        ctr = [0] * 10
        for ch in str(n):
            i = ord(ch) - ord('0')
            ctr[i] += 1
        return all(ctr[i] == i for i in range(10) if ctr[i] > 0)
    def nextBeautifulNumber(self, n: int) -> int:
        n += 1
        while not self.isBalanced(n):
            n += 1
        return n
