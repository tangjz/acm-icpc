import pandas as pd

def biggest_single_number(my_numbers: pd.DataFrame) -> pd.DataFrame:
    df = my_numbers.groupby("num").size()
    upp = df[df == 1].index.max()
    return pd.DataFrame({"num": [upp]})
