import pandas as pd

def consecutive_numbers(logs: pd.DataFrame) -> pd.DataFrame:
    return logs[logs["num"].rolling(window=3, min_periods=3).agg(lambda g: g.nunique()) == 1][["num"]].drop_duplicates().rename(columns={"num": "ConsecutiveNums"})
