n = int(raw_input())
p = int(raw_input())
m = n
t = 1
while m > 0 :
    t = t * (m % p + 1)
    m = m / p
print(n - t)
