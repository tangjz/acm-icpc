class Solution:
    def maxRepeating(self, sequence: str, word: str) -> int:
        i = 1
        cur = word
        while sequence.count(cur):
            i += 1
            cur += word
        return i - 1
