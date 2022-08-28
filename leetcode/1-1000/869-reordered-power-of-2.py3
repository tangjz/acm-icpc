class Solution:
    def __init__(self):
        self.sp = set()
        pw, upp = 1, 10 ** 9
        while pw <= upp:
            self.sp.add("".join(sorted(str(pw))))
            pw <<= 1
    
    def reorderedPowerOf2(self, n: int) -> bool:
        return "".join(sorted(str(n))) in self.sp
