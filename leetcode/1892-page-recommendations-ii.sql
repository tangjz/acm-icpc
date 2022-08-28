# Write your MySQL query statement below
select A.user_id, B.page_id, count(B.user_id) as friends_likes from ((select user1_id as user_id, user1_id as friend_id from Friendship) union (select user1_id as user_id, user2_id as friend_id from Friendship) union (select user2_id as user_id, user1_id as friend_id from Friendship) union (select user2_id as user_id, user2_id as friend_id from Friendship)) A inner join Likes B on A.friend_id = B.user_id group by A.user_id, B.page_id having sum(A.user_id = B.user_id) = 0 and friends_likes > 0;
