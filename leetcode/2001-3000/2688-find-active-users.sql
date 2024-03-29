# Write your MySQL query statement below
with cte as (select user_id, created_at, lag(created_at, 1) over(partition by user_id order by created_at asc) as last_created_at from Users) select user_id from cte where last_created_at is not null group by user_id having min(datediff(created_at, last_created_at)) <= 7;
