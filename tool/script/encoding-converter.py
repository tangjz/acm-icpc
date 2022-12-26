import os
import sys

root_path = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))

skip_ext = {"pdf", "png", "xlsx", "zip", "DS_Store"}
vis_ext = set()
upd_file = []

for root, dirs, files in os.walk(root_path):
    if ".git" in root.split("/"):
        print(f"skip {root}")
        continue
    for name in files:
        path = os.path.join(root, name)
        ext = name.split(".")[-1]
        if ext in skip_ext:
            print(f"skip {path}")
            continue
        vis_ext.add(ext)
        with open(path, "rb") as fin:
            buf = fin.read()
        old_buf = buf
        if not buf.endswith(b"\n"):
            buf += b"\n"
        buf = buf.replace(b"\r\n", b"\n").replace(b"\t\n", b"\n")
        if ext != "tex":
            buf = buf.replace(b" \n", b"\n")
        if old_buf == buf:
            continue
        upd_file.append(path)
        with open(path, "wb") as fout:
            fout.write(buf)

print(f"changed ({len(upd_file)}): {upd_file[:5]}")
print(f"ext: {sorted(vis_ext)}")
