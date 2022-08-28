# Write your MySQL query statement below
select user_id, max(diff) as biggest_window from (select user_id, datediff((lead(visit_date, 1, '2021-1-1') over(partition by user_id order by visit_date)), visit_date) as diff from UserVisits) T group by T.user_id;
