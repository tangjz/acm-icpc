# Write your MySQL query statement below
select (case when A.cnt > B.cnt then 'New York University' when A.cnt < B.cnt then 'California University' else 'No Winner' end) as winner from (select count(*) as cnt from NewYork where score >= 90) A, (select count(*) as cnt from California where score >= 90) B;
