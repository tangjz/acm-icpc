class Solution:
    def isValidSerialization(self, preorder: str) -> bool:
        rem = 1
        for item in preorder.split(','):
            rem -= 1
            if rem < 0: return False
            if item != '#': rem += 2
        return rem == 0
