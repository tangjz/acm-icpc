/**
 * @param {Array<Function>} functions
 * @return {Promise<any>}
 */
var promiseAll = async function (functions) {
    return new Promise((resolve, reject) => {
        let cnt = 0;
        const res = new Array(functions.length);
        for (let i = 0; i < functions.length; ++i) {
            functions[i]().then(v => {
                res[i] = v;
                if ((++cnt) === functions.length)
                    resolve(res);
            }).catch(e => reject(e));
        }
    });
};

/**
 * const promise = promiseAll([() => new Promise(res => res(42))])
 * promise.then(console.log); // [42]
 */
