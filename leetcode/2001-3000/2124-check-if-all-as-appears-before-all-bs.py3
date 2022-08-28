class Solution:
    def checkString(self, s: str) -> bool:
        return s == "".join(sorted(s))
