class Solution:
    def firstPalindrome(self, words: List[str]) -> str:
        for s in words:
            if s == s[::-1]:
                return s
        return ""
