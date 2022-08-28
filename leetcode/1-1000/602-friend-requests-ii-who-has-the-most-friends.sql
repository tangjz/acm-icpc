# Write your MySQL query statement below
select id, count(distinct friend_id) as num from ((select requester_id as id, accepter_id as friend_id from RequestAccepted) union (select accepter_id as id, requester_id as friend_id from RequestAccepted)) T group by id order by num desc limit 1;
