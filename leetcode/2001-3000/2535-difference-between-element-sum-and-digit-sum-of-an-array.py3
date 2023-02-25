class Solution:
    def differenceOfSum(self, nums: List[int]) -> int:
        a = sum(nums)
        nums = [sum(map(int, str(x))) for x in nums]
        b = sum(nums)
        return abs(a - b)
