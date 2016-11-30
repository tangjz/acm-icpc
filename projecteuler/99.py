import os, math
fin = open("p099_base_exp.txt", "r")
seq = fin.readlines()
for i in range(len(seq)) :
    a, b = map(int, seq[i].split(","))
    seq[i] = [a, b]
val, idx = 0, 0
for i in range(len(seq)) :
    tval = seq[i][1] * math.log(seq[i][0])
    if val < tval :
        val, idx = tval, i
print(idx + 1)
