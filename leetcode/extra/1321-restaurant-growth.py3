import pandas as pd

def restaurant_growth(customer: pd.DataFrame) -> pd.DataFrame:
    df = customer.groupby("visited_on")["amount"].sum().rolling("7D").sum().to_frame("amount")
    df["average_amount"] = (df["amount"] / 7).round(2)
    return df[df.index >= df.index.min() + pd.DateOffset(6)].reset_index()
