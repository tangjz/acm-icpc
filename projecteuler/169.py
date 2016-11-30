def f(n) :
	Hash = {}
	L, R = 0, 0
	que = []
	que.append(n)
	Hash[que[R]] = -1
	R += 1
	while L < R :
		u = que[L]
		L += 1
		if (u & 1) == 1 :
			v = (u - 1) >> 1
			if not v in Hash :
				que.append(v)
				Hash[que[R]] = 1
				R += 1
		elif u > 0 :
			v = u >> 1
			if not v in Hash :
				que.append(v)
				Hash[que[R]] = 1
				R += 1
			v -= 1
			if not v in Hash :
				que.append(v)
				Hash[que[R]] = 1
				R += 1
	que = que[::-1]
	Hash[0] = 1
	for u in que :
		if (u & 1) == 1 :
			Hash[u] = Hash[(u - 1) >> 1]
		elif u > 0 :
			v = u >> 1
			Hash[u] = Hash[v] + Hash[v - 1]
	return Hash[n]

while True :
	try :
		n = int(input())
		print(f(n))
	except :
		break
