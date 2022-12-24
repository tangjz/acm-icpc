Bronze	2014.12.16

1. 给定平面上n个点，依次走过这些点，距离为曼哈顿距离，求最多省略一个点从1走到n的最少距离和。
sol：dp，f[i][j]表示走到第i个点，用了j次跳跃的最少距离。

2. 给定一个图，求左边有障碍又能向右扩展3格或者上下方向上这样的点，输出。
sol：模拟每个点，判定。可以将边界加上障碍。

3. 给定n个人的起点和初速度，任意两个人相遇时后面的人变慢与前面的人保持距离为0，问最终有几堆人。
sol：按起点降序扫一遍，如果后面的人追得上前面的人，那么他最终的速度会和前面的人一样。

4. 给定数轴上n个整点的黑白状态，认为某个点可能是黑的当且仅当离这个点最近的已知点至少有一个是黑的，问[a,b]里有多少个整点可能是黑的。
sol：排序扫一遍。注意第一个点之前的部分和最后一个点之后的部分，其他部分直接按照四种情况区分。