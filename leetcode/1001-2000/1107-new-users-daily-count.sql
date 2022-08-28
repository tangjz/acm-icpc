# Write your MySQL query statement below
select activity_date as login_date, count(distinct user_id) as user_count from (select user_id, activity_date, (rank() over(partition by user_id order by activity_date)) as rnk from Traffic where activity = 'login') T where T.rnk = 1 and T.activity_date between '2019-04-01' and '2019-06-30' group by activity_date;
