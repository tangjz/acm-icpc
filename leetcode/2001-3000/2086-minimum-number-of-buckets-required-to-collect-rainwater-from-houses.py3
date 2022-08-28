class Solution:
    def minimumBuckets(self, street: str) -> int:
        n = len(street)
        m = 0
        seq = [ch for ch in street]
        for i in range(n):
            if seq[i] != 'H':
                continue
            lft = seq[i - 1] if i > 0 else 'H'
            rht = seq[i + 1] if i + 1 < n else 'H'
            if lft == 'H' and rht == 'H':
                return -1
            if lft == 'O' or rht == 'O':
                continue
            if rht == '.':
                seq[i + 1] = 'O'
            else:
                seq[i - 1] = 'O'
            m += 1
        return m
