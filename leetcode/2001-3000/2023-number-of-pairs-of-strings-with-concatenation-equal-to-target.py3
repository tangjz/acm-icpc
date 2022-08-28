class Solution:
    def numOfPairs(self, nums: List[str], target: str) -> int:
        ctr = 0
        n = len(nums)
        for i in range(n):
            for j in range(n):
                if i != j and nums[i] + nums[j] == target:
                    ctr += 1
        return ctr
