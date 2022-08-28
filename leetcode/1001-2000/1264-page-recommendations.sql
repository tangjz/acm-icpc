# Write your MySQL query statement below
select distinct page_id as recommended_page from Likes where user_id in (select (case when user1_id = 1 then user2_id else user1_id end) as user_id from Friendship where user1_id = 1 or user2_id = 1) and page_id not in (select page_id from Likes where user_id = 1);
