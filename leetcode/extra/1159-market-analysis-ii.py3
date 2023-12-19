import pandas as pd

def market_analysis(users: pd.DataFrame, orders: pd.DataFrame, items: pd.DataFrame) -> pd.DataFrame:
    def calc(g):
        if len(g) < 2:
            return pd.DataFrame({"item_id": []})
        return g.sort_values("order_date").iloc[[1], [1]]
    df = pd.merge(users.rename(columns={"user_id": "seller_id"}), pd.merge(orders[["order_date", "item_id", "seller_id"]].groupby("seller_id").apply(calc).reset_index(), items, on="item_id", how="inner"), on="seller_id", how="left")
    df["2nd_item_fav_brand"] = "no"
    df.loc[df["favorite_brand"] == df["item_brand"], "2nd_item_fav_brand"] = "yes"
    return df[["seller_id", "2nd_item_fav_brand"]]
