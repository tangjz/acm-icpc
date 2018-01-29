cube = PermutationGroup([[(1,2,5,12),(3,7,14,21),(9,16,22,20)],[(1,3,8,18),(4,7,16,23),(11,17,22,12)],
                         [(1,4,10,20),(2,7,17,24),(6,14,22,18)],[(3,9,19,11),(5,13,8,16),(12,21,15,23)],
                         [(4,11,13,6),(8,15,10,17),(18,23,19,24)],[(2,6,15,9),(5,14,10,19),(13,21,20,24)]])
cube_size = cube.order()
print(cube_size)
ways = [0] * 25
for item in cube.conjugacy_classes() :
    ways[len(item.an_element().cycle_type())] += item.cardinality()
for col in range(2, 11) :
    ans = 0
    for i in range(1, 25) :
        ans += ways[i] * col ** i
    assert ans % cube_size == 0
    print("color %d: %d" % (col, ans / cube_size))
