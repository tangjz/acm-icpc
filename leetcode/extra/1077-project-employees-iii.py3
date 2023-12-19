import pandas as pd

def project_employees(project: pd.DataFrame, employee: pd.DataFrame) -> pd.DataFrame:
    df = pd.merge(project, employee, on="employee_id")
    return df[df["experience_years"] == df.groupby("project_id")["experience_years"].transform("max")][["project_id", "employee_id"]]
