# Write your MySQL query statement below
select A.employee_id, A.name, count(B.employee_id) as reports_count, round(avg(B.age), 0) as average_age from Employees A inner join Employees B on A.employee_id = B.reports_to group by A.employee_id order by A.employee_id;
