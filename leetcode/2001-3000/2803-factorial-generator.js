/**
 * @param {number} n
 * @yields {number}
 */
function* factorial(n) {
    let ret = 1;
    n = Math.max(n, 1);
    for(let i = 1; i <= n; ++i) {
        ret *= i;
        yield ret;
    }
};


/**
 * const gen = factorial(2);
 * gen.next().value; // 1
 * gen.next().value; // 2
 */