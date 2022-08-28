class Solution:
    def __init__(self):
        rows = ("qwertyuiop", "asdfghjkl", "zxcvbnm")
        self.dic = {}
        for i, row in enumerate(rows):
            for ch in row:
                self.dic[ch] = i
        
    def findWords(self, words: List[str]) -> List[str]:
        return [word for word in words if len(set(self.dic[ch.lower()] for ch in word)) == 1]
