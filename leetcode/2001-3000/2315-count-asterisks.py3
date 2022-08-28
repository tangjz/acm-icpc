class Solution:
    def countAsterisks(self, s: str) -> int:
        s = s.split('|')
        return sum(s[i].count('*') for i in range(0, len(s), 2))
