class Solution:
    def countDigits(self, num: int) -> int:
        buf = str(num)
        ans = 0
        for ch in buf:
            if ch != '0' and num % int(ch) == 0:
                ans += 1
        return ans
