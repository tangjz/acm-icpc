# Write your MySQL query statement below
(select 'bull' as word, sum(content like '% bull %') as count from Files) union (select 'bear' as word, sum(content like '% bear %') as count from Files);
