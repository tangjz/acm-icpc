class Solution:
    def trans(self, tim):
        hh, mm = map(int, tim.split(":"))
        return hh * 60 + mm
    def numberOfRounds(self, loginTime: str, logoutTime: str) -> int:
        s, t = self.trans(loginTime), self.trans(logoutTime)
        if s > t:
            t += 1440
        return max(t // 15 - (s + 14) // 15, 0)
