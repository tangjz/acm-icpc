import pandas as pd

def consecutive_available_seats(cinema: pd.DataFrame) -> pd.DataFrame:
    df = cinema
    df["pre"] = df["free"].shift(1, fill_value=0)
    df["suf"] = df["free"].shift(-1, fill_value=0)
    return df[(df["free"] == 1) & ((df["pre"] == 1) | (df["suf"] == 1))][["seat_id"]].sort_values("seat_id")
