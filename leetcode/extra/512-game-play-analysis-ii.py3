import pandas as pd

def game_analysis(activity: pd.DataFrame) -> pd.DataFrame:
    def calc(g):
        return g[g["event_date"] == g["event_date"].min()][["player_id", "device_id"]]

    return activity.groupby("player_id").apply(calc)
