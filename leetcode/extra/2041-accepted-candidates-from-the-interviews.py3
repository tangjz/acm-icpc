import pandas as pd

def accepted_candidates(candidates: pd.DataFrame, rounds: pd.DataFrame) -> pd.DataFrame:
    df = rounds.groupby("interview_id")["score"].sum().reset_index()
    df = df[df["score"] > 15]
    return candidates[(candidates["years_of_exp"] >= 2) & candidates["interview_id"].isin(df["interview_id"])][["candidate_id"]]
