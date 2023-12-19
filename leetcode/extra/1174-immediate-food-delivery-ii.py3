import pandas as pd

def immediate_food_delivery(delivery: pd.DataFrame) -> pd.DataFrame:
    df = delivery[delivery["order_date"] == delivery.groupby("customer_id")["order_date"].transform("min")]
    tot = len(df)
    cnt = (df["order_date"] == df["customer_pref_delivery_date"]).sum()
    return pd.DataFrame({"immediate_percentage": [round(100 * cnt / tot, 2)]})
