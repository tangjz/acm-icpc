a, b = int(input()), int(input())
c = a % b
while c != 0L :
	a = b
	b = c
	c = a % b
print b
