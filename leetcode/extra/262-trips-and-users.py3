import pandas as pd

def trips_and_users(trips: pd.DataFrame, users: pd.DataFrame) -> pd.DataFrame:
    uid = users[users["banned"] == "No"]["users_id"]
    def calc(g):
        tot = len(g)
        cnt = (g["status"] != "completed").sum()
        print(g, tot, cnt)
        return round(cnt / tot if tot else 0, 2)

    df = trips[trips["client_id"].isin(uid) & trips["driver_id"].isin(uid) & trips["request_at"].between("2013-10-01", "2013-10-03")].groupby("request_at").apply(calc)
    if df.empty:
        return pd.DataFrame(columns=["Day", "Cancellation Rate"])
    return df.reset_index(name="Cancellation Rate").rename(columns={"request_at": "Day"})
