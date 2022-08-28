class Solution:
    def uniqueMorseRepresentations(self, words: List[str]) -> int:
        tr = [".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."]
        return len({"".join(tr[ord(ch) - ord('a')] for ch in word) for word in words})
