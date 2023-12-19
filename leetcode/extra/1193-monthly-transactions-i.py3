import pandas as pd

def monthly_transactions(transactions: pd.DataFrame) -> pd.DataFrame:
    df = transactions
    df["month"] = df["trans_date"].dt.strftime("%Y-%m")
    def calc(g):
        cnt = len(g)
        tot = g["amount"].sum()
        g = g[g["state"] == "approved"]
        a_cnt = len(g)
        a_tot = g["amount"].sum()
        return pd.DataFrame({"trans_count": [cnt], "approved_count": [a_cnt], "trans_total_amount": [tot], "approved_total_amount": [a_tot]})
    return df.groupby(["month", "country"]).apply(calc).droplevel(level=2).reset_index()
