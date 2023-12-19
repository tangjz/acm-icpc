import pandas as pd

def count_students(student: pd.DataFrame, department: pd.DataFrame) -> pd.DataFrame:
    df = pd.merge(department, student.groupby("dept_id").size().reset_index(name="student_number"), on="dept_id", how="left")
    df["student_number"].fillna(0, inplace=True)
    return df[["dept_name", "student_number"]].sort_values(by=["student_number", "dept_name"], ascending=[False, True])
