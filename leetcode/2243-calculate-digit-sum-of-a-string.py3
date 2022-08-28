class Solution:
    def digitSum(self, s: str, k: int) -> str:
        while len(s) > k:
            t = ""
            for i in range(0, len(s), k):
                t += str(sum(map(int, s[i:i+k])))
            s = t
        return s
