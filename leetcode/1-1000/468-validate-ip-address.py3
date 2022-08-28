class Solution:
    def validIPAddress(self, IP: str) -> str:
        def isIPv4(IP) :
            seq = IP.split('.')
            if len(seq) != 4 :
                return False
            for item in seq :
                try :
                    val = int(item)
                except ValueError :
                    return False
                if str(val) != item :
                    return False
                if val < 0 or val >= (1 << 8) :
                    return False
                if val == 0 and item.startswith('-') :
                    return False
            return True
        if isIPv4(IP) :
            return "IPv4"
        def isIPv6(IP) :
            seq = IP.split(':')
            if len(seq) != 8 :
                return False
            for item in seq :
                if len(item) > 4 :
                    return False
                try :
                    val = int(item, 16)
                except ValueError :
                    return False
                if val < 0 or val >= (1 << 16) :
                    return False
                if val == 0 and item.startswith('-') :
                    return False
            return True
        if isIPv6(IP) :
            return "IPv6"
        return "Neither"
