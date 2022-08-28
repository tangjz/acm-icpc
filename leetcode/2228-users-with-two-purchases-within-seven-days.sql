# Write your MySQL query statement below
select distinct user_id from (select user_id, purchase_date as cur_date, (lag(purchase_date) over(partition by user_id order by purchase_date asc, purchase_id asc)) as pre_date from Purchases) T where date_sub(cur_date, interval 7 day) <= pre_date order by user_id;
