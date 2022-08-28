class Solution:
    def isStrobogrammatic(self, num: str) -> bool:
        nxt = {'0': '0', '1': '1', '6': '9', '8': '8', '9': '6'}
        return num == "".join(nxt.get(ch, '.') for ch in num[::-1])
