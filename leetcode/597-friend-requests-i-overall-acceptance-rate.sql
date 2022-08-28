# Write your MySQL query statement below
select round(if(A.cnt > 0, B.cnt / A.cnt, 0), 2) as accept_rate from (select count(distinct concat(sender_id, send_to_id)) as cnt from FriendRequest) A, (select count(distinct concat(requester_id, accepter_id)) as cnt from RequestAccepted) B;
