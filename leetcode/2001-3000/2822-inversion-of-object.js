/**
 * @param {Object} obj
 * @return {Object}
 */
var invertObject = function(obj) {
    let ret = {};
    for(key in obj) {
        let val = obj[key];
        if(!(val in ret))
            ret[val] = [];
        ret[val].push(key);
    }
    for(key in ret)
        if(ret[key].length == 1)
            ret[key] = ret[key][0];
    return ret;
};
