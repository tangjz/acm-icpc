import pandas as pd

def find_investments(insurance: pd.DataFrame) -> pd.DataFrame:
    ids = insurance.drop_duplicates(["lat", "lon"], keep=False).index
    return insurance[insurance.duplicated("tiv_2015", keep=False) & insurance.index.isin(ids)][["tiv_2016"]].sum().round(2).to_frame("tiv_2016")
