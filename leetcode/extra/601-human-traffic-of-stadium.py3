import pandas as pd

def human_traffic(stadium: pd.DataFrame) -> pd.DataFrame:
    def calc(s):
        return s.max() - s.min() + 1 == len(s)

    df = stadium[stadium["people"] >= 100].sort_values("id")
    idx = df[df.rolling(window=3, min_periods=3)["id"].apply(calc) == True]["id"]
    return df[df["id"].isin(idx) | df["id"].isin(idx - 1) | df["id"].isin(idx - 2)]
