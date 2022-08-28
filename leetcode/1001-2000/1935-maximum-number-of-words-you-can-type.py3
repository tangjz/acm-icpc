class Solution:
    def canBeTypedWords(self, text: str, brokenLetters: str) -> int:
        cnt = 0
        for word in text.split(" "):
            for ch in word:
                if ch in brokenLetters:
                    break
            else:
                cnt += 1
        return cnt
