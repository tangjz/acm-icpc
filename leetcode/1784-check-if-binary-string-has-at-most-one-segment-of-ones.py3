class Solution:
    def checkOnesSegment(self, s: str) -> bool:
        l, r = s.find('1'), s.rfind('1')
        cnt = s.count('1')
        return cnt == 0 or (r - l + 1 == cnt)
