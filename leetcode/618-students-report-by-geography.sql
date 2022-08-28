# Write your MySQL query statement below
select max(if(continent = 'America', name, null)) as America, max(if(continent = 'Asia', name, null)) as Asia, max(if(continent = 'Europe', name, null)) as Europe from (select name, continent, (row_number() over(partition by continent order by name asc)) as row_rank from Student) T group by row_rank order by row_rank;
