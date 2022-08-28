class Solution:
    def subdomainVisits(self, cpdomains: List[str]) -> List[str]:
        ctr = {}
        for row in cpdomains:
            cnt, name = row.split(' ')
            cnt = int(cnt)
            while name != '':
                ctr[name] = ctr.get(name, 0) + cnt
                name = (name.split('.', 1) + [''])[1]
        return [str(v) + ' ' + k for k, v in ctr.items()]
