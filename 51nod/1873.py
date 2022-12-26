s, k = input().split(" ")
k = int(k)
v, chk, sz = 0, 0, 0
for ch in s :
    if '0' <= ch and ch <= '9' :
        v = v * 10 + (ord(ch) - ord('0'))
        if chk :
            sz += 1
    elif ch == '.' :
        chk = 1
while sz > 0 and v % 10 == 0 :
    sz -= 1
    v //= 10
s = str(pow(v, k))
while len(s) < sz * k :
    s = '0' + s
if sz > 0 :
    s = s[0 : len(s) - sz * k] + '.' + s[len(s) - sz * k : ]
print(s)
