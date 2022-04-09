# Write your MySQL query statement below
with A as (select experience, (sum(salary) over(partition by experience order by salary asc, employee_id asc)) as agg_salary from Candidates), B as (select agg_salary from A where experience = 'Senior' and agg_salary <= 70000), C as (select agg_salary from A where experience = 'Junior' and agg_salary <= 70000 - ifnull((select max(agg_salary) from B), 0)) (select 'Senior' as experience, count(*) as accepted_candidates from B) union all (select 'Junior' as experience, count(*) as accepted_candidates from C);