/**
 * @param {Function} fn
 * @param {number} t
 * @return {Function}
 */
var throttle = function (fn, t) {
    var idle = true, nextArgs, wrapper = function (...args) {
        nextArgs = args;
        if (!idle)
            return;
        fn(...args);
        idle = false;
        nextArgs = undefined;
        setTimeout(() => {
            idle = true;
            if (nextArgs !== undefined)
                wrapper(...nextArgs);
        }, t);
    };
    return wrapper;
};

/**
 * const throttled = throttle(console.log, 100);
 * throttled("log"); // logged immediately.
 * throttled("log"); // logged at t=100ms.
 */
