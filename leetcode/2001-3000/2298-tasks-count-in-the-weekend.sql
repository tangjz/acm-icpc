# Write your MySQL query statement below
select ifnull(sum(if(idx >= 5, cnt, 0)), 0) as weekend_cnt, ifnull(sum(if(idx < 5, cnt, 0)), 0) as working_cnt from (select weekday(submit_date) as idx, count(*) as cnt from Tasks group by idx) A;
