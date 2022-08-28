class Solution:
    def discountPrices(self, sentence: str, discount: int) -> str:
        buf = sentence.split(" ")
        for i in range(len(buf)):
            pat = buf[i]
            if len(pat) < 2 or pat[0] != '$': continue
            try:
                val = float(pat[1:])
            except Exception:
                continue
            if val < 0: continue
            buf[i] = '$%.2f' % (val * (100 - discount) / 100)
        return " ".join(buf)
