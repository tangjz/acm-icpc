maxn = 31
cnt = [0] * maxn
for x in map(int, input().split(" ")):
    cnt[x] += 1
for x in map(int, input().split(" ")):
    cnt[x] += 1
for x in map(int, input().split(" ")):
    cnt[x] += 1
fact = [1] * maxn
odd, chk3, chk5 = 0, 1, 1
for i in range(1, maxn) :
    fact[i] = fact[i - 1] * i
    odd += cnt[i] & 1
    chk3 &= cnt[i] % 3 == 0
    chk5 &= cnt[i] % 5 == 0
ans = fact[30]
for i in range(1, maxn) :
    ans //= fact[cnt[i]]
if chk5 :
    tmp = 24 * fact[6]
    for i in range(1, maxn) :
        tmp //= fact[cnt[i] // 5]
    ans += tmp
if chk3 :
    tmp = 20 * fact[10]
    for i in range(1, maxn) :
        tmp //= fact[cnt[i] // 3]
    ans += tmp
if not odd :
    tmp = 15 * fact[15]
    for i in range(1, maxn) :
        tmp //= fact[cnt[i] >> 1]
    ans += tmp
if odd == 2 :
    tmp = 15 * fact[14] * 2
    for i in range(1, maxn) :
        tmp //= fact[cnt[i] >> 1]
    ans += tmp
ans //= 60
print(ans)