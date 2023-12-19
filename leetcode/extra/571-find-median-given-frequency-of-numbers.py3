import pandas as pd

def median_frequency(numbers: pd.DataFrame) -> pd.DataFrame:
    df = numbers.sort_values("num")
    df["tmp"] = df["frequency"].cumsum()
    df = df.iloc[::-1]
    df = df[df["frequency"] >= (df["frequency"].cumsum() - df["tmp"]).abs()]
    tot = len(df)
    cnt = df["num"].sum()
    return pd.DataFrame({"median": [round(cnt / tot, 1)]})
