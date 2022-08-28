# Write your MySQL query statement below
select id from Weather t where exists (select id from Weather y where y.recordDate = t.recordDate - interval 1 day and y.temperature < t.temperature);
