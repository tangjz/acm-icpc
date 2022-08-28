class Solution:
    def halvesAreAlike(self, s: str) -> bool:
        n = len(s) // 2
        s = s.lower()
        lft, rht = s[:n], s[n:]
        diff = 0
        for ch in "aeiou":
            diff += lft.count(ch) - rht.count(ch)
        return not diff
