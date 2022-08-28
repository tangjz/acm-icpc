class Solution:
    def isNumber(self, s: str) -> bool:
        s = s.strip(' ')
        if s.count('e') + s.count('E') > 1:
            return False
        pos = s.find('e')
        if pos == -1:
            pos = s.find('E')
        return self.isDecimal(s) if pos == -1 else self.isDecimal(s[:pos]) and self.isInteger(s[pos+1:], True)
    
    def isInteger(self, s: str, allowSign: bool) -> bool:
        if allowSign and s and s[0] in ('-', '+'):
            s = s[1:]
        return len(s) > 0 and s.isdigit()
    
    def isDecimal(self, s: str) -> bool:
        if s.count('.') > 1:
            return False
        pos = s.find('.')
        if pos == -1:
            return self.isInteger(s, True)
        if len(s) == 1:
            return False
        if s[0] in ('-', '+'):
            s = s[1:]
            pos -= 1
            if len(s) == 1:
                return False
        lft = pos == 0 or self.isInteger(s[:pos], False)
        rht = pos + 1 == len(s) or self.isInteger(s[pos+1:], False)
        return lft and rht
