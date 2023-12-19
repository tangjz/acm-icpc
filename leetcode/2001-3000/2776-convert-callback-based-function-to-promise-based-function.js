/**
 * @param {Function} fn
 * @return {Function<Promise<number>>}
 */
var promisify = function (fn) {
    return async function (...args) {
        return new Promise((resolve, reject) => fn((val, err) => err ? reject(err) : resolve(val), ...args));
    }
};

/**
 * const asyncFunc = promisify(callback => callback(42));
 * asyncFunc().then(console.log); // 42
 */
