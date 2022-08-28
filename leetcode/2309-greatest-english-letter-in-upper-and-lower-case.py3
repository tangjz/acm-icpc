class Solution:
    def greatestLetter(self, s: str) -> str:
        a = {ch for ch in s if ch.lower() != ch}
        b = {ch.upper() for ch in s if ch.upper() != ch}
        c = a & b
        return max(c) if c else ""
