# Write your MySQL query statement below
select A.business_id from Events A inner join (select event_type, avg(occurences) as avg_occ from Events group by event_type) B on A.event_type = B.event_type and A.occurences > B.avg_occ group by A.business_id having count(A.event_type) > 1;
