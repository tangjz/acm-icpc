import pandas as pd

def second_degree_follower(follow: pd.DataFrame) -> pd.DataFrame:
    return follow[follow["followee"].isin(follow["follower"])].groupby("followee").size().reset_index(name="num").rename(columns={"followee": "follower"})
