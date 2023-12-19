/**
 * @param {Array} arr
 * @param {Function} fn
 * @return {Array}
 */
var sortBy = function (arr, fn) {
    return arr.sort((u, v) => fn(u) - fn(v));
};
