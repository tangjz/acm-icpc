import pandas as pd

def get_the_question(survey_log: pd.DataFrame) -> pd.DataFrame:
    def calc(g):
        print(g)
        tot = (g["action"] == "show").sum()
        cnt = (g["action"] == "answer").sum()
        return cnt / tot

    s = survey_log.groupby("question_id").apply(calc)
    idx = s[s == s.max()].index.min()
    return pd.DataFrame({"survey_log": [idx] if isinstance(idx, numpy.int64) else []})
