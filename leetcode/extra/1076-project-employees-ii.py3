import pandas as pd

def project_employees_ii(project: pd.DataFrame, employee: pd.DataFrame) -> pd.DataFrame:
    df = project.groupby("project_id")["employee_id"].count().reset_index(name="cnt")
    return df[df["cnt"] == df["cnt"].max()][["project_id"]]
