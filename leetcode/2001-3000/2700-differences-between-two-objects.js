/**
 * @param {Object|Array} obj1
 * @param {Object|Array} obj2
 * @return {Object|Array}
 */
function objDiff(obj1, obj2) {
    const isArr = (o) => Array.isArray(o);
    const isObj = (o) => typeof o === 'object' && o !== null && !isArr(o);
    const commonKeys = (o1, o2) => Object.keys(o1).filter({}.hasOwnProperty.bind(o2));
    const diff = (o1, o2) => {
        var res = null;
        if ((isArr(o1) && isArr(o2)) || (isObj(o1) && isObj(o2))) {
            const addDiff = (k, v) => {
                if (v === null)
                    return;
                if (res === null)
                    res = {};
                res[k] = v;
            };
            commonKeys(o1, o2).map(k => addDiff(k, diff(o1[k], o2[k])));
        } else if (o1 !== o2) {
            res = [o1, o2];
        }
        return res;
    };
    return diff(obj1, obj2) ?? {};
};
