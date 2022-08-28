# Write your MySQL query statement below
select A.followee as follower, count(A.follower) as num from Follow A where A.followee in (select distinct follower from Follow) group by A.followee order by A.followee asc;
