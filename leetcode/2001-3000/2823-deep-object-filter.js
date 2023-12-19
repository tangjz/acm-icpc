/**
 * @param {Object|Array} obj
 * @param {Function} fn
 * @return {Object|Array|undefined}
 */
var deepFilter = function (obj, fn) {
    if (Array.isArray(obj)) {
        const res = obj.map(i => deepFilter(i, fn)).filter(i => i !== undefined);
        return res.length > 0 ? res : undefined;
    }
    if (typeof obj === 'object' && obj !== null) {
        let empty = true;
        const res = {};
        for (const key in obj) {
            const val = deepFilter(obj[key], fn);
            if (val === undefined)
                continue;
            empty = false;
            res[key] = val;
        }
        return empty ? undefined : res;
    }
    return fn(obj) ? obj : undefined;
};
