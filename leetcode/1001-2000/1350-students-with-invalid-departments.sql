# Write your MySQL query statement below
select A.id, A.name from Students A left join Departments B on A.department_id = B.id where B.id is null;
