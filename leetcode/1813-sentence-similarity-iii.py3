class Solution:
    def areSentencesSimilar(self, sentence1: str, sentence2: str) -> bool:
        s = sentence1.split(" ")
        t = sentence2.split(" ")
        n, m = len(s), len(t)
        if n > m:
            s, t = t, s
            n, m = m, n
        pre = 0
        while pre < n and s[pre] == t[pre]:
            pre += 1
        suf = 0
        while suf < n and s[-1 - suf] == t[-1 - suf]:
            suf += 1
        return pre + suf >= n
