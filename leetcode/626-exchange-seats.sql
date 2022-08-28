# Write your MySQL query statement below
select (case when A.id % 2 = 0 then A.id - 1 when upp = A.id then A.id else A.id + 1 end) as id, A.student from Seat A, (select max(id) as upp from Seat B) as upper order by id;
