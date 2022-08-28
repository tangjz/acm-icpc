class Solution:
    def uncommonFromSentences(self, s1: str, s2: str) -> List[str]:
        ctr = {}
        for s in s1.split(" "):
            ctr[s] = ctr.get(s, 0) + 1
        for s in s2.split(" "):
            ctr[s] = ctr.get(s, 0) + 1
        return [k for k, v in ctr.items() if v == 1]
