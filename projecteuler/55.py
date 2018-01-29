ans = 0
for i in range(10000) :
    j, k = i + int(str(i)[:: -1]), 1
    while k < 50 and str(j) != str(j)[:: -1] :
        j += int(str(j)[:: -1])
        k += 1
    if str(j) != str(j)[:: -1] :
        ans += 1
print(ans)
