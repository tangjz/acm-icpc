class Solution:
    def countNumbersWithUniqueDigits(self, n: int) -> int:
        ret, prd = 1, 1
        for i in range(min(n, 10)):
            prd *= 10 - i if i > 0 else 9 - i
            ret += prd
        return ret
