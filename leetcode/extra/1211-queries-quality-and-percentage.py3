import pandas as pd

def queries_stats(queries: pd.DataFrame) -> pd.DataFrame:
    df = queries[["query_name"]]
    df["rate"] = queries["rating"] / queries["position"]
    df["poor"] = queries["rating"] < 3
    df = df.groupby("query_name").agg(quality=("rate", "mean"), tot=("poor", "count"), cnt=("poor", "sum")).reset_index()
    df["quality"] = (df["quality"] + 1e-9).round(2)
    df["poor_query_percentage"] = (100 * df["cnt"] / df["tot"]).round(2)
    return df.drop("tot", axis=1).drop("cnt", axis=1)
