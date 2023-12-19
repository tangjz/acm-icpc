import pandas as pd

def find_managers(employee: pd.DataFrame) -> pd.DataFrame:
    df = employee.groupby("managerId").size().reset_index(name="cnt")
    df = df[df["cnt"] >= 5][["managerId"]]
    return pd.merge(df, employee, left_on="managerId", right_on="id", how="inner")[["name"]]
