# Write your MySQL query statement below
select (sum(A.apple_count) + ifnull(sum(B.apple_count), 0)) as apple_count, (sum(A.orange_count) + ifnull(sum(B.orange_count), 0)) as orange_count from Boxes A left join Chests B on A.chest_id = B.chest_id;
