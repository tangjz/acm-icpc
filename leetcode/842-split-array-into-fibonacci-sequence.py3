class Solution:
    def splitIntoFibonacci(self, num: str) -> List[int]:
        n = len(num)
        for i in range(1, n - 1):
            if num[0] == '0' and i > 1:
                break
            for j in range(i + 1, n):
                if num[i] == '0' and j - i > 1:
                    break
                f = [int(num[:i]), int(num[i:j])]
                k = j
                while k < n:
                    f.append(f[-1] + f[-2])
                    if f[-1] >= (1 << 31):
                        break
                    buf = str(f[-1])
                    if num[k:k+len(buf)] != buf:
                        break
                    k += len(buf)
                if k == n:
                    return f
        return []
