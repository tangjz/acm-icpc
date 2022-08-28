class Solution:
    def findOcurrences(self, text: str, first: str, second: str) -> List[str]:
        seq = text.split(' ')
        ans = []
        for i in range(len(seq) - 2):
            if seq[i] == first and seq[i + 1] == second:
                ans += [seq[i + 2]]
        return ans
