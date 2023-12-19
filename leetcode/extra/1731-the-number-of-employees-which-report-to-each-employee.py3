import pandas as pd

def count_employees(employees: pd.DataFrame) -> pd.DataFrame:
    df = employees.groupby("reports_to").agg(reports_count=("employee_id", "count"), average_age=("age", "mean")).reset_index().rename(columns={"reports_to": "employee_id"})
    df["average_age"] = (df["average_age"] + 1e-9).round(0)
    return pd.merge(employees[["employee_id", "name"]], df, on="employee_id", how="inner").sort_values("employee_id")
