class Solution:
    def beforeAndAfterPuzzles(self, phrases: List[str]) -> List[str]:
        n = len(phrases)
        pre, suf = [], []
        for row in phrases:
            items = row.split(' ')
            pre.append(items[0])
            suf.append(items[-1])
        ret = set()
        for i in range(len(phrases)):
            for j in range(len(phrases)):
                if i != j and suf[i] == pre[j]:
                    pos = phrases[j].find(' ')
                    if pos == -1:
                        ret.add(phrases[i])
                    else:
                        ret.add(phrases[i] + phrases[j][pos:])
        return sorted(ret)
