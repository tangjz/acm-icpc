import pandas as pd

def last_passenger(queue: pd.DataFrame) -> pd.DataFrame:
    df = queue.sort_values("turn")
    df = df[df["weight"].cumsum() <= 1000]
    return df.iloc[[-1], [1]]
