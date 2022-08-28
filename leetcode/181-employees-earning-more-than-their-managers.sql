# Write your MySQL query statement below
select name as Employee from Employee A where exists (select id from Employee B where B.id = A.managerId and B.salary < A.salary);
