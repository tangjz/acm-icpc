# Write your MySQL query statement below
select distinct user_id from (select user_id, time_stamp as cur_time, (lag(time_stamp) over(partition by user_id order by time_stamp asc)) as pre_time from Confirmations) A where date_sub(A.cur_time, interval 24 hour) <= A.pre_time;
