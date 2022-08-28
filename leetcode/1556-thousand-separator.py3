class Solution:
    def thousandSeparator(self, n: int) -> str:
        buf = str(n)
        out = ""
        while len(buf) > 3 :
            out = '.' + buf[-3 : ] + out
            buf = buf[ : -3]
        out = buf + out
        return out
