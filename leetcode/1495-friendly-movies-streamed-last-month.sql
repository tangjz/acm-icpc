# Write your MySQL query statement below
select distinct A.title from Content A inner join TVProgram B on A.Kids_content = 'Y' and A.content_type = 'Movies' and A.content_id = B.content_id and date_format(B.program_date, '%Y-%m') = '2020-06';
