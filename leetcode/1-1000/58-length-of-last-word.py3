class Solution:
    def lengthOfLastWord(self, s: str) -> int:
        seq = [item for item in s.split(' ') if item]
        return len(seq[-1]) if seq else 0
