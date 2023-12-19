import pandas as pd

def actors_and_directors(actor_director: pd.DataFrame) -> pd.DataFrame:
    df = actor_director.groupby(["actor_id", "director_id"])["timestamp"].size().reset_index()
    return df[df["timestamp"] >= 3][["actor_id", "director_id"]]
