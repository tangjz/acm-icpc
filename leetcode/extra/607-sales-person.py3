import pandas as pd

def sales_person(sales_person: pd.DataFrame, company: pd.DataFrame, orders: pd.DataFrame) -> pd.DataFrame:
    df = company[company["name"] == "RED"]["com_id"]
    df = orders[orders["com_id"].isin(df)]["sales_id"].drop_duplicates()
    return sales_person[~sales_person["sales_id"].isin(df)][["name"]]
