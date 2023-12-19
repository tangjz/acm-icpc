import pandas as pd

def calculate_special_bonus(employees: pd.DataFrame) -> pd.DataFrame:
    employees["salary"] = employees.apply(lambda row: row["salary"] if row["employee_id"] % 2 > 0 and not row["name"].startswith("M") else 0, axis=1)
    return employees[["employee_id", "salary"]].sort_values(by="employee_id").rename(columns={"salary": "bonus"})
