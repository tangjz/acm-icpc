n, ans = int(raw_input()), 1
for i in range(n) :
    ans = ans * ((i << 2) + 2) // (i + 2)
print ans
