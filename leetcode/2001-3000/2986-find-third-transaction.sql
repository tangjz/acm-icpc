# Write your MySQL query statement below
with cte1 as (select user_id, spend, transaction_date, (row_number() over(partition by user_id order by transaction_date asc)) as rnk from Transactions), cte2 as (select user_id, max(spend) as pre_spend from cte1 where rnk <= 2 group by user_id) select A.user_id, A.spend as third_transaction_spend, A.transaction_date as third_transaction_date from cte1 A inner join cte2 B on A.rnk = 3 and A.user_id = B.user_id and A.spend > B.pre_spend;