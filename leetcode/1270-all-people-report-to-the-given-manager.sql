# Write your MySQL query statement below
select A.employee_id from Employees A inner join (Employees B inner join Employees C on C.manager_id = 1 and B.manager_id = C.employee_id) on A.manager_id = B.employee_id where A.employee_id <> 1;
