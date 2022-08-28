class Solution:
    def isPrefixString(self, s: str, words: List[str]) -> bool:
        cnt = 0
        for i in range(len(words)):
            cnt += len(words[i])
            if cnt == len(s):
                return s == "".join(words[:i+1])
            if cnt > len(s):
                return 0
        return 0
