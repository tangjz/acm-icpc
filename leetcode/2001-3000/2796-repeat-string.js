/**
 * @param {number} times
 * @return {string}
 */
String.prototype.replicate = function (times) {
    let ret = '', tmp = this;
    while (times > 0) {
        if (times & 1)
            ret += tmp;
        times >>= 1;
        tmp += tmp;
    }
    return ret;
}
