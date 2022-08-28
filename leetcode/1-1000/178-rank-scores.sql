# Write your MySQL query statement below
select A.score as score, (select count(distinct B.score) from Scores B where B.score >= A.score) as "rank" from Scores A order by A.score desc;
