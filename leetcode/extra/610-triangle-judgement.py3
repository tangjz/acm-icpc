import pandas as pd

def triangle_judgement(triangle: pd.DataFrame) -> pd.DataFrame:
    def calc(row):
        tot = row.sum()
        upp = row.max()
        return "Yes" if tot - upp > upp else "No"
    triangle["triangle"] = triangle.apply(calc, axis=1)
    return triangle
