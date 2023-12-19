import pandas as pd

def find_employees(employees: pd.DataFrame, salaries: pd.DataFrame) -> pd.DataFrame:
    df = pd.merge(employees, salaries, on="employee_id", how="outer")
    return df[df["name"].isna() | df["salary"].isna()][["employee_id"]].sort_values("employee_id")
