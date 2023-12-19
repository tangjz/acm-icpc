import pandas as pd

def rising_temperature(weather: pd.DataFrame) -> pd.DataFrame:
    weather.sort_values("recordDate", inplace=True)
    return weather[(weather.recordDate.diff().dt.days == 1) & (weather.temperature.diff() > 0)][["id"]]
