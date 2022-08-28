class Solution:
    def longestNiceSubstring(self, s: str) -> str:
        t = ""
        for i in range(len(s)):
            cnt = 0
            info = {}
            for j in range(i, len(s)):
                ch = s[j]
                o = ch.lower()
                f = 1 if ch == o else 2
                cnt -= info.get(o, 0) not in {0, 3}
                info[o] = info.get(o, 0) | f
                cnt += info.get(o, 0) not in {0, 3}
                if not cnt and len(t) < j - i + 1:
                    t = s[i:j+1]
        return t
