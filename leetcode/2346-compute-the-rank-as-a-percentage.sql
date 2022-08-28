# Write your MySQL query statement below
with cte as (select department_id, count(*) as cnt from Students group by department_id) select A.student_id, A.department_id, round(if(B.cnt > 1, ((rank() over(partition by A.department_id order by A.mark desc)) - 1) / (B.cnt - 1) * 100, 0), 2) as percentage from Students A inner join cte B on A.department_id = B.department_id;
