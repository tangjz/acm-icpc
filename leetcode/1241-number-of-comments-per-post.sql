# Write your MySQL query statement below
select A.post_id, count(distinct B.sub_id) as number_of_comments from (select sub_id as post_id from Submissions where parent_id is null) A left join (select sub_id, parent_id as post_id from Submissions where parent_id is not null) B on A.post_id = B.post_id group by A.post_id;
