class Solution:
    def construct2DArray(self, seq: List[int], m: int, n: int) -> List[List[int]]:
        if len(seq) != m * n:
            return []
        return [seq[i * n: (i+1) * n] for i in range(m)]
