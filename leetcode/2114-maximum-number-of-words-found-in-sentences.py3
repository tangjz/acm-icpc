class Solution:
    def mostWordsFound(self, sentences: List[str]) -> int:
        return max(s.count(' ') + 1 for s in sentences)
