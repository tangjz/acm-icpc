/**
 * @param {Function} fn
 * @return {Function}
 */
var curry = function(fn) {
    const agg = [];
    return function curried(...args) {
        agg.push(...args);
        return agg.length < fn.length ? curried : fn(...agg);
    };
};

/**
 * function sum(a, b) { return a + b; }
 * const csum = curry(sum);
 * csum(1)(2) // 3
 */
