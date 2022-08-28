# Write your MySQL query statement below
select team_id, name, (cast(old_rank as signed) - cast(new_rank as signed)) as rank_diff from (select B.team_id, B.name, (row_number() over(order by B.points desc, B.name asc)) as old_rank, (row_number() over(order by (B.points + C.points_change) desc, B.name asc)) as new_rank from TeamPoints B inner join PointsChange C on B.team_id = C.team_id) A;
