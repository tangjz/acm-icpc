# Write your MySQL query statement below
select distinct account_id from (select A.account_id, date_sub(A.cur_month, interval (row_number() over(partition by A.account_id order by A.cur_month asc)) month) as ofs from (select account_id, sum(amount) as total_income, date_format(day, '%Y-%m-01') as cur_month from Transactions where type = 'Creditor' group by account_id, cur_month) A inner join Accounts B on A.account_id = B.account_id where A.total_income > B.max_income) C group by account_id, ofs having count(*) >= 2 order by account_id asc;
