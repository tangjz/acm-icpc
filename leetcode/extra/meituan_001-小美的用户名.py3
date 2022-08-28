n = int(input())
for case in range(n):
    name = input().strip()
    print("Accept" if name and name[0].isalpha() and name.isalnum() and not name.isdigit() and not name.isalpha() else "Wrong")
