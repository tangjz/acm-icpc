# Write your MySQL query statement below
select A.id, A.year, ifnull(B.npv, 0) as npv from Queries A left join NPV B on A.id = B.id and A.year = B.year;
