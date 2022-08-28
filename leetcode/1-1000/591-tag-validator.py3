class Solution:
    def isValid(self, code: str) -> bool:
        def isValidTag(s):
            return len(s) < 10 and s.isalpha() and s.upper() == s

        n = len(code)
        i, j = code.find('<'), code.find('>')
        if i != 0 or j == -1:
            return False
        tag = code[i+1:j]
        if not isValidTag(tag) or not code.endswith("</" + tag + ">"):
            return False
        
        i = 0
        stk = []
        while i < len(code):
            if i > 0 and not stk:
                return False
            if code[i] != '<':
                i += 1
                continue
            if code[i:i+9] == "<![CDATA[":
                j = code.find("]]>", i+9)
                if j == -1:
                    return False
                i = j + 3
                continue
            if code[i:i+2] == "</":
                j = code.find(">", i+2)
                if j == -1:
                    return False
                tag = code[i+2:j]
                if not isValidTag(tag) or not stk or stk[-1] != tag:
                    return False
                stk = stk[:-1]
                i = j + 1
                continue
            j = code.find(">", i+1)
            if j == -1:
                return False
            tag = code[i+1:j]
            if not isValidTag(tag):
                return False
            stk += [tag]
            i = j + 1
        return not stk
