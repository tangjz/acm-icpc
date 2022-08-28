# Write your MySQL query statement below
select * from Users where regexp_like(mail, '^[a-zA-Z][a-zA-Z0-9\\._-]*@leetcode\\.com$')
