# Write your MySQL query statement below
select employee_id, name, salary, (dense_rank() over(order by salary asc)) as team_id from Employees A where not exists (select * from Employees B where A.salary = B.salary group by B.salary having count(*) = 1) order by salary asc, employee_id asc;
