import pandas as pd

def sales_analysis(sales: pd.DataFrame, product: pd.DataFrame) -> pd.DataFrame:
    return sales[sales["year"] == sales.groupby("product_id")["year"].transform("min")].drop("sale_id", axis=1).rename(columns={"year": "first_year"})
