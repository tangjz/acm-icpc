def mod_pow(x, k, p) :
    ret, tmp = 1, x
    while k > 0 :
        if (k & 1) == 1 :
            ret = ret * tmp % p
        tmp = tmp * tmp % p
        k = k >> 1
    return ret

n, m = map(int, input().split(" "))
pw10, length = 1, 1
for i in range(1, m + 1) :
	pw10 = (pw10 << 3) + (pw10 << 1)
	x = n % pw10
	y = mod_pow(x, length, pw10)
	cur, j = x, 1
	while j <= 10 :
		cur, j = cur * y % pw10, j + 1
		if cur == x :
			length = length * (j - 1)
			break
	if cur != x :
		length = 0
		break
print(length + 1)
