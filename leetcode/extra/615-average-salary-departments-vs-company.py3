import pandas as pd

def average_salary(salary: pd.DataFrame, employee: pd.DataFrame) -> pd.DataFrame:
    df = salary
    df["pay_month"] = df["pay_date"].dt.strftime("%Y-%m")
    df = pd.merge(df, employee, on="employee_id")
    df["c_avg"] = df.groupby("pay_month")["amount"].transform("mean")
    df["d_avg"] = df.groupby(["pay_month", "department_id"])["amount"].transform("mean")
    df["comparison"] = "same"
    df.loc[df["d_avg"] > df["c_avg"], "comparison"] = "higher"
    df.loc[df["d_avg"] < df["c_avg"], "comparison"] = "lower"
    return df[["pay_month", "department_id", "comparison"]].drop_duplicates()
