# Write your MySQL query statement below
with C as (select A.user_id as user1_id, B.user_id as user2_id from Listens A inner join Listens B on A.day = B.day and A.song_id = B.song_id and exists(select * from Friendship D where A.user_id = D.user1_id and B.user_id = D.user2_id) group by A.user_id, B.user_id, A.day having count(distinct A.song_id) >= 3) select * from C group by user1_id, user2_id;
