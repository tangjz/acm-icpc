class Solution:
    def evaluate(self, s: str, knowledge: List[List[str]]) -> str:
        t = ""
        dic = {row[0]: row[1] for row in knowledge}
        while s:
            lft = s.find('(')
            if lft == -1:
                t += s
                s = ""
                continue
            t += s[:lft]
            rht = s.find(')', lft)
            key = s[lft + 1: rht]
            t += dic.get(key, "?")
            s = s[rht + 1:]
        return t
