# Write your MySQL query statement below
with cte1 as (select max(salary) as upp from Salaries where department = 'Engineering'), cte2 as (select max(salary) as upp from Salaries where department = 'Marketing') select abs(cte1.upp - cte2.upp) as salary_difference from cte1, cte2;
