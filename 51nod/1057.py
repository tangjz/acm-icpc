def solve(l, r) :
    if l == r :
        return l
    m = l + (r - l) // 2
    return solve(l, m) * solve(m + 1, r)

if __name__ == "__main__" :
    n = int(input())
    print(solve(1, n))
