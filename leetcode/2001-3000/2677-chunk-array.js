/**
 * @param {Array} arr
 * @param {number} size
 * @return {Array}
 */
var chunk = function (arr, size) {
    var res = [];
    for (let i = 0; i < arr.length; i += size)
        res.push(arr.slice(i, i + size));
    return res;
};
