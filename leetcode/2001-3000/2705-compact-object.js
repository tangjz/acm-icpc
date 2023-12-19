/**
 * @param {Object|Array} obj
 * @return {Object|Array}
 */
var compactObject = function (obj) {
    return Array.isArray(obj) ? obj.map(compactObject).filter(Boolean) :
        typeof obj === 'object' && obj != null ? Object.entries(obj).map(([k, v]) => [k, compactObject(v)]).reduce((r, [k, v]) => Boolean(v) ? { ...r, [k]: v } : r, {}) : obj;
};
