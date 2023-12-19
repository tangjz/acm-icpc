import pandas as pd

def count_salary_categories(accounts: pd.DataFrame) -> pd.DataFrame:
    low = (accounts["income"] < 20000).sum()
    upp = (accounts["income"] > 50000).sum()
    mid = len(accounts) - low - upp
    return pd.DataFrame({"category": ["Low Salary", "Average Salary", "High Salary"], "accounts_count": [low, mid, upp]})
