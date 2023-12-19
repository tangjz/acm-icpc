import pandas as pd

def user_purchase(spending: pd.DataFrame) -> pd.DataFrame:
    def calc(s):
        return s.iloc[0] if s.nunique() == 1 else "both"
    df = spending.groupby(["user_id", "spend_date"]).agg({"platform": calc, "amount": "sum"}).reset_index()
    df = pd.merge(pd.merge(df["spend_date"].drop_duplicates(), pd.DataFrame({"platform": ["mobile", "desktop", "both"]}), how="cross"), df, on=["spend_date", "platform"], how="left")
    return df.groupby(["spend_date", "platform"]).agg(total_amount=("amount", "sum"), total_users=("user_id", "nunique")).reset_index().fillna(0)
