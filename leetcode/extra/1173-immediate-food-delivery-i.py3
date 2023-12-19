import pandas as pd

def food_delivery(delivery: pd.DataFrame) -> pd.DataFrame:
    tot = len(delivery)
    cnt = (delivery["order_date"] == delivery["customer_pref_delivery_date"]).sum()
    return pd.DataFrame({"immediate_percentage": [round(100 * cnt / tot, 2)]})
