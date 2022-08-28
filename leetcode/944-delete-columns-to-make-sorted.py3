class Solution:
    def minDeletionSize(self, strs: List[str]) -> int:
        n, m = len(strs), len(strs[0])
        ans = 0
        for i in range(m):
            a = [item[i] for item in strs]
            if a != sorted(a):
                ans += 1
        return ans
