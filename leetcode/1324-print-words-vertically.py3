class Solution:
    def printVertically(self, s: str) -> List[str]:
        seq = s.split(" ")
        n = max([len(buf) for buf in seq])
        ret = []
        for i in range(n) :
            tmp = ""
            for buf in seq :
                tmp += buf[i] if i < len(buf) else ' '
            while tmp[-1] == ' ' :
                tmp = tmp[ : -1]
            ret += [tmp]
        return ret
