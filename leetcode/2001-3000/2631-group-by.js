/**
 * @param {Function} fn
 * @return {Object}
 */
Array.prototype.groupBy = function (fn) {
    const ret = {};
    for (let i = 0; i < this.length; ++i) {
        let key = fn(this[i]);
        if (!ret.hasOwnProperty(key))
            ret[key] = [];
        ret[key].push(this[i]);
    }
    return ret;
};

/**
 * [1,2,3].groupBy(String) // {"1":[1],"2":[2],"3":[3]}
 */
