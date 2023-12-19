import pandas as pd

def reported_posts(actions: pd.DataFrame, removals: pd.DataFrame) -> pd.DataFrame:
    def calc(g):
        tot = g["post_id"].nunique()
        cnt = g[~g["remove_date"].isna()]["post_id"].nunique()
        return cnt / tot

    return pd.DataFrame({"average_daily_percent": [round(pd.merge(actions[(actions["action"] == "report") & (actions["extra"] == "spam")][["post_id", "action_date"]].drop_duplicates(), removals, on="post_id", how="left").groupby("action_date").apply(calc).reset_index(drop=True).mean() * 100, 2)]})
