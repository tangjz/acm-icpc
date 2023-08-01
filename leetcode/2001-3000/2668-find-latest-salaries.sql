# Write your MySQL query statement below
select emp_id, firstname, lastname, max(salary) as salary, department_id from Salary group by emp_id order by emp_id;