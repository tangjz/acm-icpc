/**
 * @param {Function} fn
 */
function memoize(fn) {
    let keyHash = new Map();
    let valHash = {};
    return function(...args) {
        let key = JSON.stringify(args.map(k => {
            let id = keyHash.get(k);
            if(id === undefined) {
                id = keyHash.size;
                keyHash.set(k, id);
            }
            return id;
        }));
        let val = valHash[key];
        if(val === undefined) {
            val = fn(...args);
            valHash[key] = val;
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
