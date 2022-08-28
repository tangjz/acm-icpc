# Write your MySQL query statement below
select T.name as activity from (select A.name, (rank() over(order by count(B.id) asc)) as up_rnk, (rank() over(order by count(B.id) desc)) as down_rnk from (select distinct name from Activities) A left join Friends B on A.name = B.activity group by A.name) T where T.up_rnk > 1 and T.down_rnk > 1;
