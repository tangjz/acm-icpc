# Write your MySQL query statement below
select B.id, B.name from (select distinct id from (select id, date_sub(login_date, interval (dense_rank() over(partition by id order by login_date asc)) day) as ofs from Logins group by id, login_date) T group by id, ofs having count(*) >= 5) A inner join Accounts B on A.id = B.id order by B.id;
