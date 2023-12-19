import pandas as pd

def find_employees(employee: pd.DataFrame) -> pd.DataFrame:
    df = pd.merge(employee, employee, left_on="managerId", right_on="id", how="inner")
    return df[df["salary_x"] > df["salary_y"]][["name_x"]].rename(columns={"name_x": "Employee"})
