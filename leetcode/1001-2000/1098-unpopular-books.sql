# Write your MySQL query statement below
select A.book_id, A.name from Books A left join Orders B on A.book_id = B.book_id and B.dispatch_date > '2018-06-23' where A.available_from <= '2019-05-23' group by A.book_id having ifnull(sum(B.quantity), 0) < 10;
