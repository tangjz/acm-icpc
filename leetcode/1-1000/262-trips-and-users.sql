# Write your MySQL query statement below
select A.request_at as Day, round((select count(id) from (Trips B inner join Users C on B.client_id = C.users_id and C.banned = 'No') inner join Users D on B.driver_id = D.users_id and D.banned = 'No' where B.request_at = A.request_at and B.status in ('cancelled_by_client', 'cancelled_by_driver')) / (select count(id) from (Trips B inner join Users C on B.client_id = C.users_id and C.banned = 'No') inner join Users D on B.driver_id = D.users_id and D.banned = 'No' where B.request_at = A.request_at), 2) as "Cancellation Rate" from (Trips A inner join Users C on A.client_id = C.users_id and C.banned = 'No') inner join Users D on A.driver_id = D.users_id and D.banned = 'No' where A.request_at >= '2013-10-01' and A.request_at <= '2013-10-03' group by A.request_at;
