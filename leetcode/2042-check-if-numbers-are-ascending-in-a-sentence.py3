class Solution:
    def areNumbersAscending(self, s: str) -> bool:
        last = -1
        for part in s.split(" "):
            if part and part.isdigit():
                cur = int(part)
                if last >= cur:
                    return False
                last = cur
        return True
