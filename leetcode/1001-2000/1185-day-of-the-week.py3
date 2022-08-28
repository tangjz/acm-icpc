class Solution:
    def dayOfTheWeek(self, day: int, month: int, year: int) -> str:
        from datetime import date
        return ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"][date(year, month, day).weekday()]
