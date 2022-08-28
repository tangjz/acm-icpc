class Solution:
    def numDifferentIntegers(self, word: str) -> int:
        word = "".join(ch if ord(ch) >= ord('0') and ord(ch) <= ord('9') else ' ' for ch in word)
        nums = {int(item) for item in word.split(' ') if item}
        return len(nums)
