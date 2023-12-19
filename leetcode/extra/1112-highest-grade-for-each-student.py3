import pandas as pd

def highest_grade(enrollments: pd.DataFrame) -> pd.DataFrame:
    df = enrollments[enrollments["grade"] == enrollments.groupby("student_id")["grade"].transform("max")]
    return df[df["course_id"] == df.groupby("student_id")["course_id"].transform("min")].sort_values("student_id")
