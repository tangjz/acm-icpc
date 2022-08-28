# Write your MySQL query statement below
select A.name as country from (Country A left join Person B on A.country_code = left(B.phone_number, 3)) inner join Calls C on B.id = C.caller_id or B.id = C.callee_id group by A.name having sum(if(B.id = C.caller_id, C.duration, 0) + if(B.id = C.callee_id, C.duration, 0)) / sum(if(B.id = C.caller_id, 1, 0) + if(B.id = C.callee_id, 1, 0)) > (select avg(duration) from Calls);
