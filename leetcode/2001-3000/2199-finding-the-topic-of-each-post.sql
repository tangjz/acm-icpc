# Write your MySQL query statement below
select A.post_id, ifnull(group_concat(distinct B.topic_id order by B.topic_id), 'Ambiguous!') as topic from Posts A left join Keywords B on regexp_like(A.content, concat('(^| )', B.word, '( |$)')) group by A.post_id;
