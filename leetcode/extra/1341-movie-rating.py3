import pandas as pd

def movie_rating(movies: pd.DataFrame, users: pd.DataFrame, movie_rating: pd.DataFrame) -> pd.DataFrame:
    df = movie_rating.groupby("user_id")["movie_id"].nunique()
    name = users[users["user_id"].isin(df[df == df.max()].index)]["name"].min()
    df = movie_rating[movie_rating["created_at"].dt.strftime("%Y-%m") == "2020-02"].groupby("movie_id").agg(tot=("rating", "sum"), cnt=("rating", "count"))
    df["avg"] = df["tot"] / df["cnt"]
    title = movies[movies["movie_id"].isin(df[df["avg"] == df["avg"].max()].index)]["title"].min()
    return pd.DataFrame({"results": [name, title]})
