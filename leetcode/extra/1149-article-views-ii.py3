import pandas as pd

def article_views(views: pd.DataFrame) -> pd.DataFrame:
    df = views.groupby(["view_date", "viewer_id"])["article_id"].nunique().reset_index()
    return df[df["article_id"] > 1][["viewer_id"]].drop_duplicates().rename(columns={"viewer_id": "id"}).sort_values("id")
