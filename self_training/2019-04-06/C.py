T = int(input())
for Case in range(1, T + 1) :
	N, L = map(int, input().split())
	prd = list(map(int, input().split()))
	pr = []
	for i in range(1, L) :
		lft, rht = prd[i - 1], prd[i]
		def gcd(x, y) :
			return gcd(y, x % y) if y else x
		com = gcd(lft, rht)
		if com < min(lft, rht) :
			pr += [com, lft // com, rht // com]
	pr = dict(zip(pr, [True] * len(pr)))
	while len(pr) < 26 :
		upd = False
		for item in prd :
			for pp in pr :
				if item % pp > 0 :
					continue
				qq = item // pp
				if not qq in pr :
					prd[qq], upd = True, True
					break
			if upd :
				break
		if not upd :
			break
	assert len(pr) == 26
	pr = dict(zip(sorted(list(pr.keys())), [chr(ord('A') + i) for i in range(26)]))
	for i in range(L) :
		item = prd[i]
		for pp in pr :
			if item % pp == 0 :
				prd[i] = [pr[pp], pr[item // pp]]
				break
	for i in range(2) :
		chk, ans = True, prd[0][i]
		for j in range(L) :
			vec = prd[j]
			if ans[-1] == vec[0] :
				ans += vec[1]
			elif ans[-1] == vec[1] :
				ans += vec[0]
			else :
				chk = False
				break
		if chk :
			break
	print("Case #%d: %s" % (Case, ans))
