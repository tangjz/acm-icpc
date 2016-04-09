n = int(input())
s = input()
m = len(s)
p = [0, 0]
for i in range(2, m + 1) :
    j = p[i - 1]
    while j > 0 and s[j] != s[i - 1] :
        j = p[j]
    if s[j] == s[i - 1] :
        j = j + 1
    p.append(j)
f = []
i = m
while i > 0 :
    f.append(i)
    i = p[i]
f = f[::-1]
i = 0
v = 1
ans = 0
for item in f :
    while i < item :
        v = v * n
        i = i + 1
    ans = ans + v
print(ans)
