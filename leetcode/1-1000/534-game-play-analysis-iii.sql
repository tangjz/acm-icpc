# Write your MySQL query statement below
select A.player_id, A.event_date, A.games_played_so_far from (select player_id, event_date, (sum(games_played) over(partition by player_id order by event_date asc)) as games_played_so_far from Activity) A;
