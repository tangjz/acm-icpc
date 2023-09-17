/**
 * @param {Array} arr1
 * @param {Array} arr2
 * @return {Array}
 */
var join = function(arr1, arr2) {
    const sp = {};
    [...arr1, ...arr2].forEach(obj => { sp[obj.id] = {...sp[obj.id], ...obj} });
    return [...Object.values(sp)];
};
