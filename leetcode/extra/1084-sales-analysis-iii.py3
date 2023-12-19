import pandas as pd

def sales_analysis(product: pd.DataFrame, sales: pd.DataFrame) -> pd.DataFrame:
    s1 = sales[sales["sale_date"].between("2019-01-01", "2019-03-31")]["product_id"]
    s2 = sales[~sales["sale_date"].between("2019-01-01", "2019-03-31")]["product_id"]
    return product[product["product_id"].isin(s1) & ~product["product_id"].isin(s2)].drop("unit_price", axis=1)
