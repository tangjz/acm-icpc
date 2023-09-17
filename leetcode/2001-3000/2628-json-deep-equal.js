/**
 * @param {any} o1
 * @param {any} o2
 * @return {boolean}
 */
var areDeeplyEqual = function(o1, o2) {
    if(o1 === o2)
        return true;
    if(o1 === null || o2 === null || (typeof o1) !== (typeof o2) || typeof o1 !== 'object' || Array.isArray(o1) !== Array.isArray(o2))
        return false;
    const key1 = Object.keys(o1);
    const key2 = Object.keys(o2);
    return key1.length === key2.length && key1.every(k => key2.includes(k) && areDeeplyEqual(o1[k], o2[k]));
};
