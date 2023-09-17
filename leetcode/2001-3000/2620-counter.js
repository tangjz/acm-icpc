/**
 * @param {number} n
 * @return {Function} counter
 */
var createCounter = function(n) {
    var ctr = n - 1;
    return function() {
        ctr += 1;
        return ctr;
    };
};

/**
 * const counter = createCounter(10)
 * counter() // 10
 * counter() // 11
 * counter() // 12
 */
