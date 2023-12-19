import pandas as pd

def second_highest_salary(employee: pd.DataFrame) -> pd.DataFrame:
    employee = employee.drop_duplicates(["salary"])
    return employee.sort_values("salary", ascending=False).drop("id", axis=1).rename({"salary": "SecondHighestSalary"}, axis=1).head(2).tail(1) if len(employee) >= 2 else pd.DataFrame({"SecondHighestSalary": [np.NaN]})
