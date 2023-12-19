import pandas as pd

def market_analysis(users: pd.DataFrame, orders: pd.DataFrame, items: pd.DataFrame) -> pd.DataFrame:
    return pd.merge(users, orders[orders["order_date"].dt.year == 2019], left_on="user_id", right_on="buyer_id", how="left").groupby(["user_id", "join_date"])["order_id"].count().reset_index(name="orders_in_2019").rename(columns={"user_id": "buyer_id"})
