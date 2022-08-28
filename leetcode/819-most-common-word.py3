class Solution:
    def mostCommonWord(self, paragraph: str, banned: List[str]) -> str:
        ctr = {}
        for ch in "!?,;.'": paragraph = paragraph.replace(ch, ' ')
        for item in paragraph.split(' '):
            item = item.lower()
            if not item or item in banned: continue
            if item not in ctr: ctr[item] = 0
            ctr[item] += 1
        occ = max(ctr.values())
        return [k for k, v in ctr.items() if v == occ][0]
