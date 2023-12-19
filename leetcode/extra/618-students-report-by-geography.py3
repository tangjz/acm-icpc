import pandas as pd

def geography_report(student: pd.DataFrame) -> pd.DataFrame:
    return pd.concat([student[student["continent"] == c]["name"].sort_values().to_frame(c).reset_index(drop=True) for c in ("America", "Asia", "Europe")], axis=1)
