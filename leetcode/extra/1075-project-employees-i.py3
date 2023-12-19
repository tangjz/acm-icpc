import pandas as pd

def project_employees_i(project: pd.DataFrame, employee: pd.DataFrame) -> pd.DataFrame:
    return pd.merge(project, employee, on="employee_id").groupby("project_id")["experience_years"].mean().round(2).reset_index(name="average_years")
