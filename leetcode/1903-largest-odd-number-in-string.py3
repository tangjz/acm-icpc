class Solution:
    def largestOddNumber(self, num: str) -> str:
        n = len(num)
        for i in range(n - 1, -1, -1):
            if num[i].isdigit() and (ord(num[i]) - ord('0')) % 2 == 1:
                return num[:i+1]
        return ""
