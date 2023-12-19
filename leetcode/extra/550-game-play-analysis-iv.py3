import pandas as pd

def gameplay_analysis(activity: pd.DataFrame) -> pd.DataFrame:
    df = activity[["player_id", "event_date"]].drop_duplicates()
    df["first"] = df.groupby("player_id")[["event_date"]].transform("min")
    tot = df["player_id"].nunique()
    cnt = (df["first"] + pd.DateOffset(1) == df["event_date"]).sum()
    return pd.DataFrame({"fraction": [round(cnt / tot, 2)]})
