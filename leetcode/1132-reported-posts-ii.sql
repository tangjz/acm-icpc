# Write your MySQL query statement below
select round(100 * avg(daily_rate), 2) as average_daily_percent from (select ifnull(count(distinct B.post_id) / count(distinct A.post_id), 0) as daily_rate from Actions A left join Removals B on A.extra = 'spam' and B.post_id = A.post_id where A.extra = 'spam' group by A.action_date) T;
# select ifnull(count(B.post_id) / count(A.post_id), 0) as daily_rate from Actions A left join Removals B on A.extra = 'spam' and B.post_id = A.post_id where A.extra = 'spam' group by A.action_date;
