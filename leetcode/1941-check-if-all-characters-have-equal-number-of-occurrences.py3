class Solution:
    def areOccurrencesEqual(self, s: str) -> bool:
        vis = {}
        for ch in s:
            vis[ch] = vis.setdefault(ch, 0) + 1
        return len(set(vis.values())) == 1
