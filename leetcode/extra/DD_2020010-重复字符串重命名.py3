seq = input().split(',')
ctr = {}
out = []
for item in seq:
    if item not in ctr:
        ctr[item] = 1
        out += [item]
    else:
        ctr[item] += 1
        out += ["{}_{}".format(item, ctr[item] - 2)]
print(out)
