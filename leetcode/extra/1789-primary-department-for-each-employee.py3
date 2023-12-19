import pandas as pd

def find_primary_department(employee: pd.DataFrame) -> pd.DataFrame:
    df = employee.groupby("employee_id")["primary_flag"].count()
    return pd.concat([employee[employee["employee_id"].isin(df[df == 1].index)], employee[employee["primary_flag"] == "Y"]])[["employee_id", "department_id"]].drop_duplicates()
