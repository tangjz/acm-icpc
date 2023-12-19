import pandas as pd

def active_businesses(events: pd.DataFrame) -> pd.DataFrame:
    df = events.groupby("event_type")["occurences"].transform("mean")
    df = events[events["occurences"] > df].groupby("business_id").size()
    return df[df > 1].reset_index()[["business_id"]]
