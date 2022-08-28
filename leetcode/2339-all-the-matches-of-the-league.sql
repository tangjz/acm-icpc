# Write your MySQL query statement below
select A.team_name as home_team, B.team_name as away_team from Teams A, Teams B where A.team_name <> B.team_name;
