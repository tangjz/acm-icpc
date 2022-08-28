class Solution:
    def kthDistinct(self, arr: List[str], k: int) -> str:
        ctr = {}
        for item in arr:
            ctr[item] = ctr.get(item, 0) + 1
        cnt = 0
        for item in arr:
            if ctr[item] == 1:
                cnt += 1
            if cnt == k:
                return item
        return ""
