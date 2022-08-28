# Write your MySQL query statement below
select A.employee_id from Employees A left join Employees B on A.manager_id = B.employee_id where A.salary < 30000 and A.manager_id is not null and B.employee_id is null order by A.employee_id;
