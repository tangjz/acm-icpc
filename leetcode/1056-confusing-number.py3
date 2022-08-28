class Solution:
    def confusingNumber(self, n: int) -> bool:
        num = str(n)
        nxt = {'0': '0', '1': '1', '6': '9', '8': '8', '9': '6'}
        rev = "".join(nxt.get(ch, '.') for ch in num[::-1])
        return num != rev and not rev.count('.')
