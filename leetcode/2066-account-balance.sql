# Write your MySQL query statement below
select account_id, day, (sum(if(type = 'Deposit', amount, -amount)) over(partition by account_id order by day)) as balance from Transactions;
