# Write your MySQL query statement below
select A.project_id, round(avg(B.experience_years), 2) as average_years from Project A inner join Employee B on A.employee_id = B.employee_id group by A.project_id;
