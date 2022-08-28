# Write your MySQL query statement below
select A.contest_id, round(100 * count(A.user_id) / C, 2) as percentage from Register A, (select count(*) as C from Users) as B group by A.contest_id order by percentage desc, A.contest_id asc;
