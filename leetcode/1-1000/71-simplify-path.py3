class Solution:
    def simplifyPath(self, path: str) -> str:
        ret = []
        for item in path.split("/"):
            if not item or item == '.':
                continue
            if item == '..':
                if ret:
                    ret = ret[:-1]
                continue
            ret += [item]
        return "/" + "/".join(ret)
