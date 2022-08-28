class Solution:
    def countPrefixes(self, words: List[str], s: str) -> int:
        return sum([1 if s.startswith(w) else 0 for w in words])
