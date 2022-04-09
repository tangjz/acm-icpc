# Write your MySQL query statement below
select distinct from_id as user_id from (select from_id, to_id, date(call_time) as call_day, (row_number() over(partition by from_id, date(call_time) order by call_time asc)) as up_rnk, (row_number() over(partition by from_id, date(call_time) order by call_time desc)) as down_rnk from ((select caller_id as from_id, recipient_id as to_id, call_time from Calls) union (select recipient_id as from_id, caller_id as to_id, call_time from Calls)) T1) T2 where up_rnk = 1 or down_rnk = 1 group by from_id, call_day having count(distinct to_id) = 1;