class Solution:
    def dayOfYear(self, buf: str) -> int:
        from datetime import date, timedelta
        yy, mm, dd = map(int, buf.split('-'))
        dt = date(yy, mm, dd) - date(yy, 1, 1)
        return dt.days + 1
