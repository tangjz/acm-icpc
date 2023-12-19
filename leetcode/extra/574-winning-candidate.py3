import pandas as pd

def winning_candidate(candidate: pd.DataFrame, vote: pd.DataFrame) -> pd.DataFrame:
    tf = vote.groupby("candidateId").size().reset_index(name="cnt")
    tf = tf[tf["cnt"] == tf["cnt"].max()][["candidateId"]]
    return pd.merge(candidate, tf, left_on="id", right_on="candidateId", how="inner")[["name"]]
