class Solution:
    def mergeAlternately(self, a: str, b: str) -> str:
        c = ""
        while a or b:
            if a:
                c += a[0]
                a = a[1:]
            if b:
                c += b[0]
                b = b[1:]
        return c
