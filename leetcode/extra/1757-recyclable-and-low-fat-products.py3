import pandas as pd

def find_products(products: pd.DataFrame) -> pd.DataFrame:
    return products[(products["low_fats"] == "Y") & (products["recyclable"] == "Y")][["product_id"]]
