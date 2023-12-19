/**
 * @param {Array} arr
 * @return {(string | number | boolean | null)[][]}
 */
var jsonToMatrix = function (arr) {
    let flatten = (obj, p, res) => {
        for (const [k, v] of Object.entries(obj))
            if (typeof v !== 'object' || v === null) {
                res[p + k] = v;
            } else {
                flatten(v, p + k + ".", res);
            }
    };
    let newArr = arr.map(i => {
        let res = {};
        flatten(i, "", res);
        return res;
    });
    keys = Object.keys(newArr.reduce((r, i) => ({ ...r, ...i }), {})).sort();
    return newArr.reduce((r, i) => [...r, keys.map(k => k in i ? i[k] : '')], [keys]);
};
