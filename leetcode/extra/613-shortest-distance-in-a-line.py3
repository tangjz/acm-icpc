import pandas as pd

def shortest_distance(point: pd.DataFrame) -> pd.DataFrame:
    df = point.sort_values("x").diff()
    return pd.DataFrame({"shortest": [int(df.min())]})
