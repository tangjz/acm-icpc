/**
 * @param {Object | Array} obj
 * @return {boolean}
 */
var isEmpty = function(obj) {
    for(let o in obj)
        return false;
    return true;
};
