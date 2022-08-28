class Solution:
    def reorderSpaces(self, text: str) -> str:
        seq = [item for item in text.split(" ") if item]
        cnt = text.count(" ")
        mid = cnt // (len(seq) - 1) if len(seq) > 1 else 1
        cnt -= mid * (len(seq) - 1)
        return (" " * mid).join(seq) + " " * cnt
