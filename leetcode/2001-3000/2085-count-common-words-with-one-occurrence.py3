class Solution:
    def countWords(self, words1: List[str], words2: List[str]) -> int:
        def getOnce(words):
            ctr = {}
            for item in words:
                ctr[item] = ctr.get(item, 0) + 1
            return {item for item, occ in ctr.items() if occ == 1}
        return len(getOnce(words1) & getOnce(words2))
