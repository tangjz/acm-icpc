Hash = {}

def dfs(cur, num, lim) :
    global Hash
    if tuple(cur) in Hash :
        return
    Hash[tuple(cur)] = 1
    for i in range(len(cur)) :
        if num // cur[i] - cur[i] > lim :
            continue
        nxt = []
        for j in range(len(cur)) :
            nxt.append(cur[j])
        nxt[i] = num // cur[i] - cur[i]
        nxt.sort()
        dfs(nxt, num // cur[i] * (num // cur[i] - cur[i]), lim)
    return

def check(cur) :
    for i in range(1, len(cur)) :
        if cur[i - 1] == cur[i] :
            return False
    return True

n = int(input())
dfs([1, 1, 3, 3, 4], 36, n)
ans = []
for item in Hash:
    #if check(item) == True :
    ans.append(item)
ans.sort()
if len(ans) == 0 :
    print("No Solution")
else :
    print(len(ans))
    for item in ans :
        a, b, c, d, e = item[0 : 5]
        print("%d %d %d %d %d" % (a, b, c, d, e))
