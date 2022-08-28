# Write your MySQL query statement below
select distinct A.num as ConsecutiveNums from (Logs A inner join Logs B on A.id = B.id - 1 and A.num = B.num) inner join Logs C on B.id = C.id - 1 and B.num = C.num;
