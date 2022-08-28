# Write your MySQL query statement below
(select A.name as results from Users A inner join MovieRating B on A.user_id = B.user_id group by A.user_id order by count(B.movie_id) desc, A.name asc limit 1) union (select A.title as results from Movies A inner join MovieRating B on A.movie_id = B.movie_id and date_format(B.created_at, "%Y-%m") = '2020-02' group by A.movie_id order by avg(B.rating) desc, A.title asc limit 1);