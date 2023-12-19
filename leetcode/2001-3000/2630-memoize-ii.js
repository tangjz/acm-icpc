/**
 * @param {Function} fn
 * @return {Function}
 */
function memoize(fn) {
    let keyHash = new Map();
    let valHash = new Map();
    return function (...args) {
        let key = JSON.stringify(args.map(k => {
            if (!keyHash.has(k))
                keyHash.set(k, keyHash.size);
            return keyHash.get(k);
        }));
        if (!valHash.has(key))
            valHash.set(key, fn(...args));
        return valHash.get(key);
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
