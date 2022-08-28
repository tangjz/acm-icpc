# Write your MySQL query statement below
select A.name from Employee A inner join Employee B on A.id = B.managerId group by B.managerId having count(B.id) >= 5;
