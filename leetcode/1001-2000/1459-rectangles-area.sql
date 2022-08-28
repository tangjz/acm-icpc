# Write your MySQL query statement below
select A.id as p1, B.id as p2, (abs(A.x_value - B.x_value) * abs(A.y_value - B.y_value)) as area from Points A inner join Points B on A.id < B.id and A.x_value <> B.x_value and A.y_value <> B.y_value order by area desc, A.id asc, B.id asc;
