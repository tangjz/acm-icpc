class Solution:
    def numberOfBeams(self, bank: List[str]) -> int:
        ctr = [row.count("1") for row in bank]
        ans, las = 0, 0
        for item in ctr:
            if not item: continue
            ans += las * item
            las = item
        return ans
