import pandas as pd

def swap_salary(salary: pd.DataFrame) -> pd.DataFrame:
    salary["sex"].replace({"m": "f", "f": "m"}, inplace=True)
    return salary
