/**
 * @param {Function} fn
 */
function memoize(fn) {
    var cache = {};
    return function(...args) {
        var key = JSON.stringify(args);
        var val = cache[key];
        if(val === undefined) {
            val = fn(...args);
            cache[key] = val;
        }
        return val;
    }
}


/**
 * let callCount = 0;
 * const memoizedFn = memoize(function (a, b) {
 *	 callCount += 1;
 *   return a + b;
 * })
 * memoizedFn(2, 3) // 5
 * memoizedFn(2, 3) // 5
 * console.log(callCount) // 1
 */
