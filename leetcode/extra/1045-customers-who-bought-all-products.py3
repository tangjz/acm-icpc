import pandas as pd

def find_customers(customer: pd.DataFrame, product: pd.DataFrame) -> pd.DataFrame:
    df = pd.merge(customer.drop_duplicates(), product, on="product_key", how="inner").groupby("customer_id")["product_key"].count()
    return df[df == len(product)].index.to_frame("customer_id")
