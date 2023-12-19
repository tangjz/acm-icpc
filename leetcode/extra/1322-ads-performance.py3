import pandas as pd

def ads_performance(ads: pd.DataFrame) -> pd.DataFrame:
    def calc(g):
        cnt1 = sum(g == "Clicked")
        cnt0 = sum(g == "Viewed")
        return round(100 * cnt1 / (cnt0 + cnt1), 2) if cnt0 + cnt1 else 0.00

    return ads.groupby("ad_id")["action"].apply(calc).reset_index().rename(columns={"action": "ctr"}).sort_values(by=["ctr", "ad_id"], ascending=[False, True])
