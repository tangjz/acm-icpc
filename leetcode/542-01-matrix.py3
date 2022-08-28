class Solution:
    def updateMatrix(self, mat: List[List[int]]) -> List[List[int]]:
        n, m = len(mat), len(mat[0])
        dis = [[-1] * m for i in range(n)]
        que = []
        for i in range(n):
            for j in range(m):
                if mat[i][j] == 0:
                    que.append((i, j))
                    dis[i][j] = 0
        i = 0
        while i < len(que):
            x, y = que[i]
            for dx in (-1, 0, 1):
                for dy in (-1, 0, 1):
                    if dx * dy != 0:
                        continue
                    x2, y2 = x + dx, y + dy
                    if x2 >= 0 and x2 < n and y2 >= 0 and y2 < m and dis[x2][y2] == -1:
                        dis[x2][y2] = dis[x][y] + 1
                        que.append((x2, y2))
            i += 1
        return dis
