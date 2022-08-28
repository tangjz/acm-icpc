# Write your MySQL query statement below
select A.player_id, A.player_name, (sum(B.Wimbledon = A.player_id) + sum(B.Fr_open = A.player_id) + sum(B.US_open = A.player_id) + sum(B.Au_open = A.player_id)) as grand_slams_count from Players A, Championships B group by A.player_id having grand_slams_count > 0;
