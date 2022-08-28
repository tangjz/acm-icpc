class Solution:
    def toTime(self, time: str) -> int:
        hh, mm = int(time[:2]), int(time[-2:])
        return hh * 60 + mm
        
    def convertTime(self, current: str, correct: str) -> int:
        a, b = self.toTime(current), self.toTime(correct)
        dt = abs(a - b)
        ans = dt // 60
        dt %= 60
        ans += dt // 15
        dt %= 15
        ans += dt // 5
        dt %= 5
        ans += dt
        return ans
