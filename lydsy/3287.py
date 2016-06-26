ans = [0, 1, 2, 3, 4, 5, 6, 9, 12, 16, 20, 27, 36, 48, 64, 81, 108, 144, 192, 256]
while True :
    n = int(raw_input())
    if n < 15 :
        print(ans[n])
    else :
        print(ans[n % 5 + 15] * int(4 ** (n // 5 - 3)))
