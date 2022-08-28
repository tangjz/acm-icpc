# Write your MySQL query statement below
select employee_id from Employees where not exists (select employee_id from Salaries where Employees.employee_id = Salaries.employee_id) union select employee_id from Salaries where not exists (select employee_id from Employees where Employees.employee_id = Salaries.employee_id) order by employee_id;
