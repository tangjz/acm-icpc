CREATE PROCEDURE PivotProducts()
BEGIN
	# Write your MySQL query statement below.
    set @@session.group_concat_max_len = 1000000;
    set @cmd := concat('select product_id,', (select group_concat(concat(' sum(if(store = "', store, '", price, null)) as ', store)) from (select distinct store from Products order by store) T), ' from Products group by product_id');
    prepare exec_cmd from @cmd;
    execute exec_cmd;
    deallocate prepare exec_cmd;
END
