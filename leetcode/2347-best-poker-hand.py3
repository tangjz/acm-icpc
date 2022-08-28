class Solution:
    def bestHand(self, ranks: List[int], suits: List[str]) -> str:
        if len(set(suits)) == 1:
            return "Flush"
        ctr = {}
        for x in ranks:
            ctr[x] = ctr.get(x, 0) + 1
        rk = max(ctr.values())
        if rk >= 3:
            return "Three of a Kind"
        if rk == 2:
            return "Pair"
        return "High Card"
