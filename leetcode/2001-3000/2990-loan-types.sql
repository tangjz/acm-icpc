# Write your MySQL query statement below
with cte1 as (select distinct user_id from Loans where loan_type = 'Refinance'), cte2 as (select distinct user_id from Loans where loan_type = 'Mortgage') select A.user_id from cte1 A inner join cte2 B on A.user_id = B.user_id order by A.user_id asc;
