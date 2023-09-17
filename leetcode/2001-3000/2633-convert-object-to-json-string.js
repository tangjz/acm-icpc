/**
 * @param {any} object
 * @return {string}
 */
var jsonStringify = function(object) {
    if(typeof object === 'string')
        return '"' + object + '"';
    if(object === null || typeof object !== 'object')
        return String(object);
    if(Array.isArray(object))
        return '[' + object.map(v => jsonStringify(v)).join(",") + ']';
    return '{' + Object.keys(object).map(k => '"' + k + '":' + jsonStringify(object[k])).join(",") + '}';
};
