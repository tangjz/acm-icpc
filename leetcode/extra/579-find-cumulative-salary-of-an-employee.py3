import pandas as pd

def cumulative_salary(employee: pd.DataFrame) -> pd.DataFrame:
    def calc2(s):
        upp = s.index[-1]
        return s[[i for i in s.index if i > upp - 3]].sum()

    def calc(g):
        g = g.sort_values("month")
        g = g.drop(g.index[-1])
        g[["month", "salary"]] = g[["month", "salary"]].rolling(window=3, min_periods=1, on="month").apply(calc2)
        return g.sort_values("month", ascending=False).rename(columns={"salary": "Salary"})

    return employee.groupby("id").apply(calc)
