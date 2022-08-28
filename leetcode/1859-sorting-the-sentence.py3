class Solution:
    def sortSentence(self, s: str) -> str:
        s = s.split(" ")
        t = [""] * len(s)
        for item in s:
            pos = ord(item[-1]) - ord('1')
            t[pos] = item[:-1]
        return " ".join(t)
