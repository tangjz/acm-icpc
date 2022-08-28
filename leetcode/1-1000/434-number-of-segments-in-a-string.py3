class Solution:
    def countSegments(self, s: str) -> int:
        return len([item for item in s.split(" ") if item])
