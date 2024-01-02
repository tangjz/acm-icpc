# Write your MySQL query statement below
with cte as (select student_id, (assignment1 + assignment2 + assignment3) as score from Scores) select (max(score) - min(score)) as difference_in_score from cte;
