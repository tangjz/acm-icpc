/**
 * @param {object} obj
 * @return {object}
 */
var undefinedToNull = function(obj) {
    if(Array.isArray(obj)) {
        for(let i = 0; i < obj.length; ++i)
            obj[i] = undefinedToNull(obj[i]);
        return obj;
    }
    if(typeof obj === 'object' && obj !== null) {
        for(const key in obj)
            obj[key] = undefinedToNull(obj[key]);
    }
    return obj === undefined ? null : obj;
};

/**
 * undefinedToNull({"a": undefined, "b": 3}) // {"a": null, "b": 3}
 * undefinedToNull([undefined, undefined]) // [null, null]
 */
