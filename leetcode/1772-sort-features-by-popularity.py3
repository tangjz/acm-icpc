class Solution:
    def sortFeatures(self, features: List[str], responses: List[str]) -> List[str]:
        rnk = {name: i for i, name in enumerate(features)}
        ctr = {name: 0 for name in features}
        for rsp in responses:
            vis = set()
            for word in rsp.split(' '):
                if word in ctr and word not in vis:
                    ctr[word] += 1
                    vis.add(word)
        return sorted(features, key=lambda x: (-ctr[x], rnk[x]))
