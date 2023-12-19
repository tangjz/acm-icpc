import pandas as pd

def reported_posts(actions: pd.DataFrame) -> pd.DataFrame:
    return actions[(actions["action_date"] == "2019-07-04") & (actions["action"] == "report")][["extra", "post_id"]].groupby("extra")["post_id"].nunique().reset_index(name="report_count").rename(columns={"extra": "report_reason"})
