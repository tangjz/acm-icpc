# Write your MySQL query statement below
select A.symbol as metal, B.symbol as nonmetal from Elements A inner join Elements B on A.type = 'Metal' and B.type = 'Nonmetal';
