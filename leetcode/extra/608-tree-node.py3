import pandas as pd

def tree_node(tree: pd.DataFrame) -> pd.DataFrame:
    tree["type"] = "Inner"
    tree.loc[~tree["id"].isin(tree["p_id"]), "type"] = "Leaf"
    tree.loc[tree["p_id"].isna(), "type"] = "Root"
    return tree[["id", "type"]]
