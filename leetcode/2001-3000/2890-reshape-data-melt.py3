import pandas as pd

def meltTable(report: pd.DataFrame) -> pd.DataFrame:
    return report.melt(id_vars=["product"], value_vars=["quarter_" + str(i) for i in range(1, 5)], var_name="quarter", value_name="sales")
