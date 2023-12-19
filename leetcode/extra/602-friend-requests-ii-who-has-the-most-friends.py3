import pandas as pd

def most_friends(request_accepted: pd.DataFrame) -> pd.DataFrame:
    df = request_accepted[["requester_id", "accepter_id"]].rename(columns={"requester_id": "id", "accepter_id": "fid"})
    df = pd.concat([df, df[["fid", "id"]].rename(columns={"id": "fid", "fid": "id"})]).groupby("id")["fid"].nunique().reset_index(name="num")
    return df[df["num"] == df["num"].max()]
