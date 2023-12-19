import pandas as pd

def top_three_salaries(employee: pd.DataFrame, department: pd.DataFrame) -> pd.DataFrame:
    def calc(g):
        s = g["salary"].drop_duplicates()
        if len(s) < 3:
            return g
        low = s.sort_values(ascending=False).iloc[2]
        return g[g["salary"] >= low]

    if employee.empty:
        return pd.DataFrame(columns=["Department", "Employee", "Salary"])
    return pd.merge(employee.groupby("departmentId")[["name", "salary"]].apply(calc).reset_index(), department, left_on="departmentId", right_on="id", how="inner")[["name_y", "name_x", "salary"]].rename(columns={"name_y": "Department", "name_x": "Employee", "salary": "Salary"})
