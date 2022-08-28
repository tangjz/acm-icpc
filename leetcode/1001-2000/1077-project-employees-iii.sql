# Write your MySQL query statement below
select T.project_id, T.employee_id from (select A.project_id, A.employee_id, (rank() over(partition by A.project_id order by B.experience_years desc)) as rnk from Project A inner join Employee B on A.employee_id = B.employee_id) T where T.rnk = 1;
