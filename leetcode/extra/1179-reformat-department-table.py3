import pandas as pd

def reformat_table(department: pd.DataFrame) -> pd.DataFrame:
    return department.pivot(index="id", columns="month", values="revenue").add_suffix("_Revenue").reindex(columns=[mon + "_Revenue" for mon in ("Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec")]).reset_index()
