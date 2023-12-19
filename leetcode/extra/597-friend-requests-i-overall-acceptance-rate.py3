import pandas as pd

def acceptance_rate(friend_request: pd.DataFrame, request_accepted: pd.DataFrame) -> pd.DataFrame:
    tot = friend_request.drop_duplicates(["sender_id", "send_to_id"]).size
    cnt = request_accepted.drop_duplicates(["requester_id", "accepter_id"]).size
    return pd.DataFrame({"accept_rate": [round(cnt / tot if tot else 0, 2)]})
