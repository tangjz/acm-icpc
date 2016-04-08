def solve(l, r) :
    if l == r :
        return l
    m = l + (r - l) // 2
    return solve(l, m) * solve(m + 1, r)

def print_line(x) :
    x = str(x)
    for i in range(0, len(x), 1000) :
        j = i + 1000
        if j > len(x) :
            j = len(x)
        print(x[i : j])

if __name__ == "__main__" :
    n = int(input())
    print_line(solve(1, n))

