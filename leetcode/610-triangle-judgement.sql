# Write your MySQL query statement below
select x, y, z, if(x + y + z > greatest(x, y, z) * 2, 'Yes', 'No') as triangle from Triangle;
