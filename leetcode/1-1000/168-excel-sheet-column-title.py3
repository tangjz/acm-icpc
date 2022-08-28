class Solution:
    def convertToTitle(self, columnNumber: int) -> str:
        n, pw = 0, 1
        while True:
            n, pw = n + 1, pw * 26
            if columnNumber <= pw:
                buf = ""
                columnNumber -= 1
                for i in range(n):
                    buf += chr(ord('A') + columnNumber % 26)
                    columnNumber //= 26
                return buf[::-1]
            columnNumber -= pw
        return ""
