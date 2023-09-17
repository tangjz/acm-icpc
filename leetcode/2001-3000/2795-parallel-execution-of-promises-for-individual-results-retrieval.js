/**
 * @param {Array<Function>} functions
 * @return {Promise}
 */
var promiseAllSettled = function(functions) {
    return new Promise((resolve, _) => {
        let rem = functions.length;
        const res = new Array(rem);
        functions.forEach((fn, idx) => {
            fn().then((val) => {
                res[idx] = {
                    status: 'fulfilled',
                    value: val,
                };
            }).catch((err) => {
                res[idx] = {
                    status: 'rejected',
                    reason: err,
                };
            }).finally(() => {
                --rem;
                if(rem === 0)
                    resolve(res);
            });
        });
    });
};


/**
 * const functions = [
 *    () => new Promise(resolve => setTimeout(() => resolve(15), 100))
 * ]
 * const time = performance.now()
 *
 * const promise = promiseAllSettled(functions);
 *
 * promise.then(res => {
 *     const out = {t: Math.floor(performance.now() - time), values: res}
 *     console.log(out) // {"t":100,"values":[{"status":"fulfilled","value":15}]}
 * })
 */
