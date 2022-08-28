# Write your MySQL query statement below
select A.player_id, A.device_id from (select player_id, device_id, (rank() over(partition by player_id order by event_date asc)) as row_rank from Activity) A where A.row_rank = 1;
