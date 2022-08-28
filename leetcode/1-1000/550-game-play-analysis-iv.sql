# Write your MySQL query statement below
select round(count(B.player_id) / count(A.player_id), 2) as fraction from (select player_id, min(event_date) as event_date from Activity group by player_id) A left join Activity B on A.player_id = B.player_id and A.event_date = date_sub(B.event_date, interval 1 day);
