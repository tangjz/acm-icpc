import pandas as pd

def sales_analysis(sales: pd.DataFrame, product: pd.DataFrame) -> pd.DataFrame:
    return sales.groupby("product_id")["quantity"].sum().reset_index(name="total_quantity")
