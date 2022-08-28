class Solution:
    def minCost(self, startPos: List[int], homePos: List[int], rowCosts: List[int], colCosts: List[int]) -> int:
        x1, y1 = startPos
        x2, y2 = homePos
        ans = 0
        if x1 > x2:
            ans += sum(rowCosts[x2: x1])
        else:
            ans += sum(rowCosts[x1 + 1: x2 + 1])
        if y1 > y2:
            ans += sum(colCosts[y2: y1])
        else:
            ans += sum(colCosts[y1 + 1: y2 + 1])
        return ans
