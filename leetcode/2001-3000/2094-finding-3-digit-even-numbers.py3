class Solution:
    def findEvenNumbers(self, digits: List[int]) -> List[int]:
        ctr = {}
        for i in digits:
            
            ctr[i] = ctr.get(i, 0) + 1
        ret = []
        for i in range(100, 1000, 2):
            bad = False
            need = {}
            for ch in str(i):
                j = ord(ch) - ord('0')
                need[j] = need.get(j, 0) + 1
                bad |= need[j] > ctr.get(j, 0)
            if not bad:
                ret += [i]
        return ret
