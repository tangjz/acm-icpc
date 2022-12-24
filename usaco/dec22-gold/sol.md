A

每个物品：u + v X[i] >= C[i] 时获得 P[i]

限制：sum(u) <= A, sum(v) <= B

最大化：sum([u + v X[i] >= C[i]] P[i])

解：按 X[i] 排序，至多一个组合使用，前面的全 u=0，后面的全 v=0

B

不太好写

做两遍，第二遍 reverse 数组

每一遍对每个起点分别维护一条倾角非降的视野

线段树维护，每次：
- 查询前缀倾角，判断能否加入一个向量
- 更新后缀倾角，比当前向量小角度的都删除（顺序扫，过程中维护是否停止）
- 查询整体数量

lambda func 会因为调用次数过多而被卡常，需要改写

C

最大化诱导子图代价：min(deg) * size

一个点可以在 min(deg) = K 时出现：邻居前 K 大 deg 都够大

按某种顺序枚举加点，过程中维护 min(deg) * size
-> 原图 deg 降序不对，反例是一个三元环带一个三元链
-> 按 min(deg) 删点的逆序是对的