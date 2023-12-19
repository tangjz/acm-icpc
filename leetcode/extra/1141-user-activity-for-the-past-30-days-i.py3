import pandas as pd

def user_activity(activity: pd.DataFrame) -> pd.DataFrame:
    return activity[activity["activity_date"].between("2019-06-28", "2019-07-27")].groupby("activity_date")["user_id"].nunique().reset_index(name="active_users").rename(columns={"activity_date": "day"})
