class Solution:
    def findDuplicate(self, paths: List[str]) -> List[List[str]]:
        mp = {}
        for info in paths:
            items = info.split(" ")
            prefix, items = items[0], items[1:]
            for item in items:
                pos = item.find("(")
                name = prefix + "/" + item[:pos]
                cont = item[pos+1:-1]
                mp[cont] = mp.get(cont, []) + [name]
        return [v for v in mp.values() if len(v) > 1]
