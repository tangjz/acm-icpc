/**
 * @param {any} obj1
 * @param {any} obj2
 * @return {any}
 */
var deepMerge = function(obj1, obj2) {
    if(Array.isArray(obj1) && Array.isArray(obj2)) {
        const len1 = obj1.length, len2 = obj2.length;
        const res = [];
        for(let i = 0; i < len1 || i < len2; ++i)
            if(i < len1 && i < len2) {
                res.push(deepMerge(obj1[i], obj2[i]));
            } else if(i < len1) {
                res.push(obj1[i]);
            } else {
                res.push(obj2[i]);
            }
        return res;
    }
    const isObj = (obj) => typeof obj === 'object' && obj !== null && !Array.isArray(obj);
    if(isObj(obj1) && isObj(obj2)) {
        const res = {};
        for(const key in obj1)
            if(key in obj2) {
                res[key] = deepMerge(obj1[key], obj2[key]);
            } else {
                res[key] = obj1[key];
            }
        for(const key in obj2)
            if(!(key in obj1)) {
                res[key] = obj2[key];
            }
        return res;
    }
    return obj2;
};

/**
 * let obj1 = {"a": 1, "c": 3}, obj2 = {"a": 2, "b": 2};
 * deepMerge(obj1, obj2); // {"a": 2, "c": 3, "b": 2}
 */
