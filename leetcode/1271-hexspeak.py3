class Solution:
    def toHexspeak(self, num: str) -> str:
        mp = {'0': 'O', '1': 'I'}
        buf = hex(int(num))[2:].upper()
        nxt = "".join([ch if not ch.isdigit() else mp.get(ch, '') for ch in buf])
        return nxt if len(buf) == len(nxt) else "ERROR"
