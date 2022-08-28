class Solution:
    def countValidWords(self, sentence: str) -> int:
        ans = 0
        for word in sentence.split(" "):
            if not word:
                continue
            bad = False
            found = False
            for p in "!.,":
                pos = word.find(p)
                if pos != -1 and pos != len(word) - 1:
                    bad = True
                    break
                if pos != -1:
                    found = True
            if bad:
                continue
            if found:
                word = word[:-1]
            occ = word.count('-')
            if occ > 1 or (occ == 1 and (word[0] == '-' or word[-1] == '-')):
                continue
            for ch in word:
                if ch.isdigit():
                    bad = True
                    break
            if not bad:
                ans += 1
                # print(word)
        # print()
        return ans
