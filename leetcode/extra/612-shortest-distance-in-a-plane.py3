import pandas as pd

def shortest_distance(point2_d: pd.DataFrame) -> pd.DataFrame:
    df = point2_d.reset_index()
    df = pd.merge(df, df, how="cross")
    df = df[df["index_x"] != df["index_y"]]
    dis2 = ((df["x_x"] - df["x_y"]) ** 2 + (df["y_x"] - df["y_y"]) ** 2).min()
    return pd.DataFrame({"shortest": [round(sqrt(dis2), 2)]})
