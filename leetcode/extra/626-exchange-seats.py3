import pandas as pd

def exchange_seats(seat: pd.DataFrame) -> pd.DataFrame:
    df = seat
    df["old_student"] = df["student"]
    ids = seat.index % 2 == 1
    df.iloc[ids, 1] = df["old_student"].shift(1).iloc[ids]
    ids = (seat.index % 2 == 0) & (seat.index != len(seat) - 1)
    df.iloc[ids, 1] = df["old_student"].shift(-1).iloc[ids]
    return df[["id", "student"]]
