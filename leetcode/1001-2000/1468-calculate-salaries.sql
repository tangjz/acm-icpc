# Write your MySQL query statement below
select company_id, employee_id, employee_name, round(case when upp < 1000 then A.salary when upp > 10000 then A.salary * 0.51 else A.salary * 0.76 end) as salary from (select company_id, employee_id, employee_name, salary, (max(salary) over(partition by company_id)) as upp from Salaries) A;
