class Solution:
    def reformatDate(self, date: str) -> str:
        import datetime
        date = date[:2] + date[4:] if date[1].isdigit() else date[:1] + date[3:]
        dt = datetime.datetime.strptime(date,'%d %b %Y')
        return datetime.datetime.strftime(dt,'%Y-%m-%d')
