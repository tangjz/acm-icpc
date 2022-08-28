class Solution:
    def smallestNumber(self, num: int) -> int:
        buf = sorted(str(abs(num)))
        if num < 0:
            buf = ["-"] + buf[::-1]
        elif num > 0 and buf[0] == '0':
            pos = 0
            while buf[pos] == '0':
                pos += 1
            buf = [buf[pos]] + buf[:pos] + buf[pos+1:]
        return int("".join(buf))
