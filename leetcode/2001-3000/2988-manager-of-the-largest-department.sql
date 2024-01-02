# Write your MySQL query statement below
with cte1 as (select dep_id, count(emp_id) as num from Employees group by dep_id), cte2 as (select dep_id from cte1 where num = (select max(num) as max_num from cte1)) select A.emp_name as manager_name, A.dep_id from Employees A inner join cte2 B on A.position = 'Manager' and A.dep_id = B.dep_id order by A.dep_id asc;
