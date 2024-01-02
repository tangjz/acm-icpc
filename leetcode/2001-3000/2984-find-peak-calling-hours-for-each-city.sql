# Write your MySQL query statement below
with cte1 as (select city, hour(call_time) as calling_hour, count(caller_id) as number_of_calls from Calls group by city, calling_hour), cte2 as (select city, max(number_of_calls) as peak_number_of_calls from cte1 group by city) select A.city, A.calling_hour as peak_calling_hour, A.number_of_calls from cte1 A inner join cte2 B on A.city = B.city and A.number_of_calls = B.peak_number_of_calls order by peak_calling_hour desc, A.city desc;