class Solution:
    def isCircularSentence(self, sentence: str) -> bool:
        words = sentence.split(' ')
        n = len(words)
        for i in range(n):
            j = i - 1 if i > 0 else n - 1
            a = words[i][0]
            b = words[j][-1]
            if a != b:
                return False
        return True
