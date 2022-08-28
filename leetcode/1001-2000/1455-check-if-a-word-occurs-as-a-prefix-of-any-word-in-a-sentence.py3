class Solution:
    def isPrefixOfWord(self, sentence: str, searchWord: str) -> int:
        seq = sentence.split(" ")
        for i in range(len(seq)) :
            if seq[i].startswith(searchWord) :
                return i + 1
        return -1
