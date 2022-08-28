# Write your MySQL query statement below
select B.name as Department, A.name as Employee, A.salary as Salary from Employee A inner join Department B on A.departmentId = B.id where A.salary >= ifnull((select distinct C.salary from Employee C where C.departmentId = A.departmentId order by C.salary desc limit 1 offset 2), 0);
