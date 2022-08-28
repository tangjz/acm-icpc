# Please write a DELETE statement and DO NOT write a SELECT statement.
# Write your MySQL query statement below
delete A from Person A inner join Person B on A.email = B.email where B.id < A.id;
