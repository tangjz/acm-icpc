class Solution:
    def largestInteger(self, num: int) -> int:
        seq = list(map(int, str(num)))
        pos = [[], []]
        for i in range(len(seq)):
            pos[seq[i] & 1] += [i]
        for i in range(2):
            vals = []
            for j in pos[i]:
                vals += [seq[j]]
            vals.sort()
            for j in pos[i]:
                seq[j] = vals[-1]
                vals = vals[:-1]
        return int("".join(map(str, seq)))
