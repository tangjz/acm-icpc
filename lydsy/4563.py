n, a, b = int(raw_input()), 1, 0
for i in range(1, n) :
    a, b = b, (a + b) * i
print b
