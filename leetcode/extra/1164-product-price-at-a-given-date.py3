import pandas as pd

def price_at_given_date(products: pd.DataFrame) -> pd.DataFrame:
    df = products[products["change_date"] <= "2019-08-16"]
    df = df[df["change_date"] == df.groupby("product_id")["change_date"].transform("max")][["product_id", "new_price"]].rename(columns={"new_price": "price"})
    return pd.merge(products[["product_id"]].drop_duplicates(), df, on="product_id", how="left").fillna(10)
