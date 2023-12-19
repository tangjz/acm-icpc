import pandas as pd

def count_rich_customers(store: pd.DataFrame) -> pd.DataFrame:
    cnt = store[store["amount"] > 500]["customer_id"].nunique()
    return pd.DataFrame({"rich_count": [cnt]})
