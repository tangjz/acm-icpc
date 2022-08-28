# Write your MySQL query statement below
select A.name from Candidate A inner join Vote B on A.id = B.candidateId group by A.id order by count(B.id) desc limit 1;
