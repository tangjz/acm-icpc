import pandas as pd

def rearrange_products_table(products: pd.DataFrame) -> pd.DataFrame:
    seq = []
    for key in ("store1", "store2", "store3"):
        df = products[products[key].notnull()][["product_id", key]].rename(columns={key: "price"})
        df["store"] = key
        seq.append(df[["product_id", "store", "price"]])
    return pd.concat(seq)
