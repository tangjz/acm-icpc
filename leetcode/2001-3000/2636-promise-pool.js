/**
 * @param {Function[]} functions
 * @param {number} n
 * @return {Promise<any>}
 */
var promisePool = async function (functions, n) {
    let init = functions.slice(0, n);
    let remain = functions.slice(n);
    let pick = () => remain.length && remain.shift()().then(pick);
    return Promise.all(init.map((fn) => fn().then(pick)));
};

/**
 * const sleep = (t) => new Promise(res => setTimeout(res, t));
 * promisePool([() => sleep(500), () => sleep(400)], 1)
 *   .then(console.log) // After 900ms
 */
