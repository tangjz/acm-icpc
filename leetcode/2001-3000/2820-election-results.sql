# Write your MySQL query statement below
with cte1 as (select voter, count(candidate) as cnt from Votes group by voter), cte2 as (select A.candidate as candidate, sum(1 / B.cnt) as cnt from Votes A inner join cte1 B on A.candidate is not null and A.voter = B.voter group by A.candidate), cte3 as (select max(cnt) as upp from cte2) select A.candidate as candidate from cte2 A, cte3 B where A.cnt = B.upp order by candidate asc;
