import pandas as pd

def user_activity(activity: pd.DataFrame) -> pd.DataFrame:
    df = activity[activity["activity_date"].between("2019-06-28", "2019-07-27")]
    tot = df["user_id"].nunique()
    cnt = df["session_id"].nunique()
    return pd.DataFrame({"average_sessions_per_user": [round(cnt / tot if tot else 0, 2)]})
