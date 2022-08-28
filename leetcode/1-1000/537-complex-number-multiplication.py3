class Solution:
    def complexNumberMultiply(self, num1: str, num2: str) -> str:
        def decode(s):
            p = s.find('+')
            return int(s[:p]), int(s[p+1:-1])
        
        def encode(r, i):
            return "%d+%di" % (r, i)
        
        r1, i1 = decode(num1)
        r2, i2 = decode(num2)
        return encode(r1 * r2 - i1 * i2, r1 * i2 + r2 * i1)
