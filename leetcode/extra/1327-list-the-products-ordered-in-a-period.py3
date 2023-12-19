import pandas as pd

def list_products(products: pd.DataFrame, orders: pd.DataFrame) -> pd.DataFrame:
    df = pd.merge(products, orders[orders["order_date"].dt.strftime("%Y-%m") == "2020-02"], on="product_id", how="inner").groupby("product_name")["unit"].sum()
    return df[df >= 100].reset_index()
