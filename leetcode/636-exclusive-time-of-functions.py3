class Solution:
    def exclusiveTime(self, n: int, logs: List[str]) -> List[int]:
        ctr = [0 for i in range(n)]
        stk = []
        las = 0
        for row in logs:
            items = row.split(':')
            idx, typ, tim = int(items[0]), items[1] == 'end', int(items[2])
            if typ:
                tim += 1
            if stk:
                ctr[stk[-1]] += tim - las
            stk = stk[:-1] if typ else stk + [idx]
            las = tim
        return ctr
