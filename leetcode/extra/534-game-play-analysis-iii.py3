import pandas as pd

def gameplay_analysis(activity: pd.DataFrame) -> pd.DataFrame:
    df = activity.sort_values("event_date")
    df["games_played_so_far"] = df.groupby("player_id")["games_played"].cumsum()
    return df[["player_id", "event_date", "games_played_so_far"]]
