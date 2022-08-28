# Write your MySQL query statement below
select A.candidate_id from Candidates A left join Rounds B on A.years_of_exp >= 2 and A.interview_id = B.interview_id where A.years_of_exp >= 2 group by A.candidate_id having sum(B.score) > 15;
