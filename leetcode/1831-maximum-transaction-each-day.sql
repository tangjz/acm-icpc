# Write your MySQL query statement below
select T.transaction_id from (select transaction_id, (rank() over(partition by day(Transactions.day) order by amount desc)) as rnk from Transactions) T where T.rnk = 1 order by T.transaction_id;
