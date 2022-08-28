# Write your MySQL query statement below
with A as ((select "Android" as platform) union all (select "IOS" as platform) union all (select "Web" as platform)), B as ((select "Reading" as experiment_name) union all (select "Sports" as experiment_name) union all (select "Programming" as experiment_name))
select A.platform, B.experiment_name, count(C.experiment_id) as num_experiments from (A inner join B on 1 = 1) left join Experiments C on A.platform = C.platform and B.experiment_name = C.experiment_name group by A.platform, B.experiment_name;
