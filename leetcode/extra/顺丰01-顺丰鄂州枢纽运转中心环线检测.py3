class Solution:
    def hasCycle(self, graph: str) -> bool:
        e = {}
        deg = {}
        for item in graph.split(','):
            u, v = map(int, item.split('->'))
            if u not in deg:
                deg[u] = 0
                e[u] = []
            if v not in deg:
                deg[v] = 0
                e[v] = []
            e[u].append(v)
            deg[v] += 1
        que = []
        for u in deg:
            if not deg[u]:
                que.append(u)
        i = 0
        while i < len(que):
            u = que[i]
            for v in e[u]:
                deg[v] -= 1
                if not deg[v]:
                    que.append(v)
            i += 1
        return len(que) != len(deg)
