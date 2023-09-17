/**
 * @param {number[]} arr
 * @param {Function} fn
 * @return {number[]}
 */
var map = function(arr, fn) {
    const res = [];
    for(let i = 0; i < arr.length; ++i)
        res.push(fn(arr[i], i));
    return res;
};
