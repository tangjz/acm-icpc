import pandas as pd

def average_selling_price(prices: pd.DataFrame, units_sold: pd.DataFrame) -> pd.DataFrame:
    df = pd.merge(prices, units_sold, on="product_id", how="outer")
    pids = df["product_id"].drop_duplicates()
    df = df[(df["start_date"] <= df["purchase_date"]) & (df["purchase_date"] <= df["end_date"])]
    df["total_price"] = df["price"] * df["units"]
    df = df.groupby("product_id")[["total_price", "units"]].sum()
    df["average_price"] = (df["total_price"] / df["units"]).round(2)
    return df.reindex(pids).fillna(0).reset_index()[["product_id", "average_price"]]
