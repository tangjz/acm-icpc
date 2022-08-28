class Solution:
    def reorderLogFiles(self, logs: List[str]) -> List[str]:
        logs = [(idx, info[-1].isdigit(), info.split(" ")) for idx, info in enumerate(logs)]
        logs.sort(key=lambda s: (1, s[0]) if s[1] else (0, s[2][1:], s[2][0]))
        return [" ".join(s[2]) for s in logs]
