# Write your MySQL query statement below
with cte1 as ((select user1, user2 from Friends) union (select user2 as user1, user1 as user2 from Friends)), cte2 as (select count(distinct user1) as cnt from cte1) select cte1.user1 as user1, round(100 * count(distinct cte1.user2) / cte2.cnt, 2) as percentage_popularity from cte1, cte2 group by cte1.user1 order by cte1.user1 asc;
