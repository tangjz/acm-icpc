# Write your MySQL query statement below
select product_id, max(if(store = 'store1', price, null)) as store1, max(if(store = 'store2', price, null)) as store2, max(if(store = 'store3', price, null)) as store3 from Products group by product_id;
