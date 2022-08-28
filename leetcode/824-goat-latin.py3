class Solution:
    def toGoatLatin(self, S: str) -> str:
        words = S.split(' ')
        vowels = set("aeiou")
        for i in range(len(words)) :
            firstLetter = words[i][0]
            if not firstLetter.lower() in vowels :
                words[i] = words[i][1:] + firstLetter
            words[i] += "m" + "a" * (i + 2)
        return " ".join(words)
