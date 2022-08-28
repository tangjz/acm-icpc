class Solution:
    def minimumSum(self, num: int) -> int:
        buf = sorted(str(num))
        vals = ["", ""]
        for i in range(len(buf)):
            vals[i % 2] += buf[i]
        return sum(map(int, vals))
