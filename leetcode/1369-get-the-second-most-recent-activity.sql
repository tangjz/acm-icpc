# Write your MySQL query statement below
(select username, activity, startDate, endDate from (select username, activity, startDate, endDate, (row_number() over(partition by username order by endDate desc)) as rnk from UserActivity) T where rnk = 2) union (select username, activity, startDate, endDate from UserActivity group by username having count(endDate) = 1);
