# Write your MySQL query statement below
select ad_id, round(ifnull(100 * sum(action = 'Clicked') / (sum(action = 'Clicked') + sum(action = 'Viewed')), 0), 2) as ctr from Ads group by ad_id order by ctr desc, ad_id asc;
