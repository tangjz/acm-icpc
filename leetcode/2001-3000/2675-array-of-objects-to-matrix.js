/**
 * @param {Array} arr
 * @return {Matrix}
 */
var jsonToMatrix = function(arr) {
    flatten = (i, p = []) => Object.entries(i).reduce(
        (r, [k, v]) => typeof v !== 'object' || v === null ?
            { ...r, [[...p, k].join(".")]: v} :
            { ...r, ...flatten(v, [...p, k])},
        {},
    );
    newArr = arr.map(i => flatten(i));
    keys = Object.keys(newArr.reduce((r, i) => ({ ...r, ...i }), {})).sort();
    return newArr.reduce((r, i) => [ ...r, keys.map(k => k in i ? i[k] : '') ], [ keys ]);
};
