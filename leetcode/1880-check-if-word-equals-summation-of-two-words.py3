def toInt(buf: str) -> int:
    return int("".join(chr(ord(ch) - ord('a') + ord('0')) for ch in buf))

class Solution:
    def isSumEqual(self, firstWord: str, secondWord: str, targetWord: str) -> bool:
        a, b, c = toInt(firstWord), toInt(secondWord), toInt(targetWord)
        return a + b == c
