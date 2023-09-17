/**
 * @param {Object} obj
 * @return {Function}
 */
Function.prototype.bindPolyfill = function(obj) {
    const sym = Symbol();
    obj[sym] = this;
    return (...args) => obj[sym](...args);
}
