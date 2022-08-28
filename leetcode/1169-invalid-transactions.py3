class Solution:
    def invalidTransactions(self, transactions: List[str]) -> List[str]:
        n = len(transactions)
        bad = [False] * n
        events = [row.split(',') for row in transactions]
        for i in range(n):
            if int(events[i][2]) >= 1000:
                bad[i] = True
        for i in range(n):
            for j in range(n):
                if bad[i] and bad[j]:
                    continue
                if events[i][0] == events[j][0] and events[i][3] != events[j][3] and -60 <= int(events[i][1]) - int(events[j][1]) <= 60:
                    bad[i] = True
                    bad[j] = True
        return [transactions[i] for i in range(n) if bad[i]]
