class Solution:
    def findRestaurant(self, list1: List[str], list2: List[str]) -> List[str]:
        mp1 = {key: idx for idx, key in enumerate(list1)}
        mp2 = {key: idx for idx, key in enumerate(list2)}
        com = set(mp1) & set(mp2)
        dis = min(mp1[k] + mp2[k] for k in com)
        return [k for k in com if mp1[k] + mp2[k] == dis]
