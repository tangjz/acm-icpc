class Solution:
    def isAlienSorted(self, words: List[str], order: str) -> bool:
        nxt = {ch: chr(ord('a') + idx) for idx, ch in enumerate(order)}
        for idx in range(len(words)):
            words[idx] = "".join(nxt[ch] for ch in words[idx])
        return sorted(words) == words
