/**
 * @param {number[]} arr
 * @param {Function} fn
 * @return {number[]}
 */
var filter = function (arr, fn) {
    const res = [];
    for (let i = 0; i < arr.length; ++i)
        fn(arr[i], i) && res.push(arr[i]);
    return res;
};
