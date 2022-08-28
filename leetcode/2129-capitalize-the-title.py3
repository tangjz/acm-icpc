class Solution:
    def capitalizeTitle(self, title: str) -> str:
        return " ".join([item[:1].upper() + item[1:].lower() if len(item) > 2 else item.lower() for item in title.split(' ')])
