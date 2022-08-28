# Write your MySQL query statement below
select A.user_id as seller_id, if(A.favorite_brand = B.item_brand, 'yes', 'no') as 2nd_item_fav_brand from (Users A left join (select seller_id, item_id, (row_number() over(partition by seller_id order by order_date)) as rnk from Orders) C on A.user_id = C.seller_id and C.rnk = 2) left join Items B on C.item_id = B.item_id;
