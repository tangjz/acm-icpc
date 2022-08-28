class Solution:
    def maskPII(self, s: str) -> str:
        if s.count('@'):
            name, domain = s.split('@')
            if len(name) > 1:
                name = name[:1] + '*' * 5 + name[-1:]
            return name.lower() + '@' + domain.lower()
        s = [ch for ch in s if ch.isdigit()]
        n = len(s)
        s = ('*' * 3 + '-') * 2 + ''.join(s[-4:])
        if n > 10:
            s = '+' + '*' * (n - 10) + '-' + s
        return s
