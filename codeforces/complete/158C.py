n = int(input())
cur = [""]
for tt in range(n) :
    buf = input()
    if buf.startswith("pwd") :
        print("/".join(cur + [""]))
    else :
        buf = buf.split(" ", 1)[1]
        buf = buf.split("/")
        if buf[0] == "" :
            cur = [""]
            buf = buf[1 : ]
            if buf[0] == "" :
                buf = []
        for item in buf :
            if item == ".." :
                cur = cur[ : -1]
            else :
                cur += [item]
