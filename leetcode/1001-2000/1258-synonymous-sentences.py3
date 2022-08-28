class Solution:
    def generateSentences(self, synonyms: List[List[str]], text: str) -> List[str]:
        idx, dsu, sp = {}, {}, {}
        
        def get_idx(pat):
            if pat in idx:
                return idx[pat]
            sz = len(idx)
            idx[pat] = sz
            dsu[sz] = -1
            sp[sz] = {pat}
            return sz
        
        def dsu_find(x):
            if dsu[x] < 0:
                return x
            dsu[x] = dsu_find(dsu[x])
            return dsu[x]
        
        def dsu_merge(u, v):
            u, v = map(dsu_find, (u, v))
            if u == v:
                return 0
            if dsu[u] < dsu[v]:
                u, v = v, u
            if dsu[u] == dsu[v]:
                dsu[v] -= 1
            sp[v] |= sp[u]
            del sp[u]
            dsu[u] = v
            return 1

        for fir, sec in synonyms:
            dsu_merge(get_idx(fir), get_idx(sec))

        ret = [[]]
        for word in text.split(' '):
            nxt = []
            u = dsu_find(get_idx(word))
            for row in ret:
                nxt += [row + [rep] for rep in sp[u]]
            ret = nxt
        return sorted([" ".join(row) for row in ret])
