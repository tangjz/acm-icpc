/**
 * @param {Array} arr
 * @param {number} depth
 * @return {Array}
 */
var flat = function (arr, n) {
    if (n === 0)
        return arr;
    const ret = [];
    for (let i = 0; i < arr.length; ++i)
        Array.isArray(arr[i]) ? ret.push(...flat(arr[i], n - 1)) : ret.push(arr[i]);
    return ret;
};
