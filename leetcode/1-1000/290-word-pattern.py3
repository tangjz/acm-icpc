class Solution:
    def wordPattern(self, pattern: str, s: str) -> bool:
        words = s.split(' ')
        if len(words) != len(pattern):
            return False
        ch_to_word, word_to_ch = {}, {}
        for i in range(len(words)):
            ch = pattern[i]
            word = words[i]
            if ch not in ch_to_word:
                ch_to_word[ch] = word
            elif ch_to_word[ch] != word:
                return False
            if word not in word_to_ch:
                word_to_ch[word] = ch
            elif word_to_ch[word] != ch:
                return False
        return True
