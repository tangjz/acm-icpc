import sys

def exgcd(a, b) :
	r_cur, r_nxt = a, b
	s_cur, t_cur = 1, 0
	s_nxt, t_nxt = 0, 1
	while r_nxt != 0 :
		q_cur = r_cur // r_nxt
		r_cur, r_nxt = r_nxt, r_cur - q_cur * r_nxt
		s_cur, s_nxt = s_nxt, s_cur - q_cur * s_nxt
		t_cur, t_nxt = t_nxt, t_cur - q_cur * t_nxt
	return s_cur, t_cur, r_cur

n, m = map(int, input().split(' '))
a1, m1 = 0, 1
for i in range(n) :
	m2, a2 = map(int, input().split(' '))
	x, y, r = exgcd(m1, m2)
	if (a2 - a1) % r != 0 :
		print('he was definitely lying')
		sys.exit(0)
	x = (a2 - a1) % m2 * x % m2 // r
	a1 += m1 * x
	m1 *= m2 // r
if a1 > m :
	print('he was probably lying')
else :
	print(a1)
