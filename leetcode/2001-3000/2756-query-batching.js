/**
 * @param {Function} queryMultiple
 * @param {number} t
 */
var QueryBatcher = function (queryMultiple, t) {
    let wait = false, que = [];
    const check = async () => {
        if (wait || que.length === 0)
            return;
        wait = true;
        setTimeout(() => { wait = false; check(); }, t);

        let tmpQue = [];
        [que, tmpQue] = [tmpQue, que];
        const res = await queryMultiple(tmpQue.map(i => i[0]));
        const resQue = tmpQue.map(i => i[1]);
        for (let i = 0; i < resQue.length; ++i)
            resQue[i](res[i]);
    };
    this.append = (key, res) => {
        que.push([key, res]);
        check();
    };
};

/**
 * @param {string} key
 * @returns Promise<string>
 */
QueryBatcher.prototype.getValue = async function (key) {
    return new Promise((resolve, _) => {
        this.append(key, resolve);
    });
};

/**
 * async function queryMultiple(keys) {
 *   return keys.map(key => key + '!');
 * }
 *
 * const batcher = new QueryBatcher(queryMultiple, 100);
 * batcher.getValue('a').then(console.log); // resolves "a!" at t=0ms
 * batcher.getValue('b').then(console.log); // resolves "b!" at t=100ms
 * batcher.getValue('c').then(console.log); // resolves "c!" at t=100ms
 */
