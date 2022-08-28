class Solution:
    def removeAnagrams(self, words: List[str]) -> List[str]:
        ret = []
        for word in words:
            if not ret or sorted(ret[-1]) != sorted(word):
                ret.append(word)
        return ret
