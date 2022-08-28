# Write your MySQL query statement below
select count(distinct account_id) as accounts_count from Subscriptions A where start_date <= '2021-12-31' and end_date >= '2021-01-01' and not exists (select * from Streams B where A.account_id = B.account_id and year(B.stream_date) = 2021);
