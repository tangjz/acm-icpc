/**
 * @param {*} obj
 * @param {*} classFunction
 * @return {boolean}
 */
var checkIfInstanceOf = function (obj, classFunction) {
    while (obj != null) {
        if (obj.constructor === classFunction)
            return true;
        obj = obj.__proto__;
    }
    return false;
};

/**
 * checkIfInstanceOf(new Date(), Date); // true
 */
