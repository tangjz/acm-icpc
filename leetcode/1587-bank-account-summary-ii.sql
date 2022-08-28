# Write your MySQL query statement below
select name, sum(amount) as balance from Users inner join Transactions on Users.account = Transactions.account group by Users.account having balance > 10000;
