import pandas as pd

def count_occurrences(files: pd.DataFrame) -> pd.DataFrame:
    df = pd.DataFrame({"word": ["bull", "bear"]})
    df["count"] = df.apply(lambda row: files["content"].str.contains(" " + row["word"] + " ").sum(), axis=1)
    return df
