# Write your MySQL query statement below
select T.user1_id, T.user2_id from (select A.user_id as user1_id, B.user_id as user2_id, (rank() over(order by count(A.follower_id) desc)) as rnk from Relations A inner join Relations B on A.follower_id = B.follower_id and A.user_id < B.user_id group by A.user_id, B.user_id) T where T.rnk = 1;
