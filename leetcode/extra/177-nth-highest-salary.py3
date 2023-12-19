import pandas as pd

def nth_highest_salary(employee: pd.DataFrame, N: int) -> pd.DataFrame:
    col = "getNthHighestSalary(%d)" % N
    employee = employee.drop_duplicates(["salary"])
    return employee[["salary"]].sort_values(by="salary").tail(N).head(1).rename(columns={"salary": col}) if N > 0 and len(employee) >= N else pd.DataFrame({col: [np.NaN]})
