# Write your MySQL query statement below
select question_id as survey_log from SurveyLog group by question_id order by (sum(action = 'answer') / sum(action = 'show')) desc, question_id asc limit 1;
