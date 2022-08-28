# Write your MySQL query statement below
select A.session_id from Playback A left join Ads B on A.customer_id = B.customer_id and B.timestamp between A.start_time and A.end_time where B.customer_id is null;
