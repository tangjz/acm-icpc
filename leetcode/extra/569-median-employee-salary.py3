import pandas as pd

def median_employee_salary(employee: pd.DataFrame) -> pd.DataFrame:
    def calc(g):
        n = len(g)
        g = g.sort_values(["salary", "id"])
        print(g)
        if n % 2 > 0:
            return g.iloc[[n // 2]]
        return g.iloc[[(n - 1) // 2, n // 2]]
    return employee.groupby("company").apply(calc)
