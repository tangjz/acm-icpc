# Write your MySQL query statement below
select A.id, A.month, (A.salary + ifnull(B.salary, 0) + ifnull(C.salary, 0)) as salary from (((select B.id, max(B.month) as month from Employee B group by B.id) T inner join Employee A on A.id = T.id and A.month < T.month) left join Employee B on B.id = A.id and B.month = A.month - 1) left join Employee C on C.id = A.id and C.month = A.month - 2 order by A.id asc, A.month desc;