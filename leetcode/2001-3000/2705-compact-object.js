/**
 * @param {Object} obj
 * @return {Object}
 */
var compactObject = function(obj) {
    return Array.isArray(obj) ? obj.map(compactObject).filter(Boolean) :
        typeof obj === 'object' && obj != null ? Object.entries(obj).map(([k, v]) => [k, compactObject(v)]).reduce((r, [k, v]) => Boolean(v) ? { ...r, [k]: v } : r, {}) : obj;
};
