class Solution:
    def divisorSubstrings(self, num: int, k: int) -> int:
        ans = 0
        buf = str(num)
        for i in range(0, len(buf) - k + 1):
            val = int(buf[i:i+k])
            if val > 0 and num % val == 0:
                ans += 1
        return ans
