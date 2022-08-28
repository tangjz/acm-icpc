class Solution:
    def sumOfDigits(self, nums: List[int]) -> int:
        return (1 + sum(ord(ch) - ord('0') for ch in str(min(nums)))) % 2
