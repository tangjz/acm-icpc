/**
 * @param {Array} keysArr
 * @param {Array} valuesArr
 * @return {Object}
 */
var createObject = function (keysArr, valuesArr) {
    let ret = {};
    for (let i = 0; i < keysArr.length; ++i) {
        let key = String(keysArr[i]);
        if (!(key in ret))
            ret[key] = valuesArr[i];
    }
    return ret;
};
