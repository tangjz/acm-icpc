class Solution:
    def numUniqueEmails(self, emails: List[str]) -> int:
        ret = set()
        for email in emails:
            local, domain = email.split('@')
            pos = local.find('+')
            if pos != -1:
                local = local[:pos]
            ret.add(local.replace('.', '') + '@' + domain)
        return len(ret)
