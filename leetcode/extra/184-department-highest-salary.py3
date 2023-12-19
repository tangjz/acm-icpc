import pandas as pd

def department_highest_salary(employee: pd.DataFrame, department: pd.DataFrame) -> pd.DataFrame:
    df = employee.groupby("departmentId").apply(lambda g: g[g["salary"] == g["salary"].max()]).reset_index(drop=True)
    return pd.merge(df, department, left_on="departmentId", right_on="id", how="inner", suffixes=("_a", "_b"))[["name_b", "name_a", "salary"]].rename(columns={"name_b": "Department", "name_a": "Employee", "salary": "Salary"})
