class Solution:
    def isAdditiveNumber(self, num: str) -> bool:
        n = len(num)
        for i in range(1, n - 1):
            if num[0] == '0' and i > 1:
                break
            for j in range(i + 1, n):
                if num[i] == '0' and j - i > 1:
                    break
                f0, f1 = int(num[:i]), int(num[i:j])
                k = j
                while k < n:
                    f0, f1 = f1, f0 + f1
                    buf = str(f1)
                    if num[k:k+len(buf)] != buf:
                        break
                    k += len(buf)
                if k == n:
                    return True
        return False
