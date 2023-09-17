/**
 * @param {Function} fn
 * @param {Array} args
 * @return {Function}
 */
var partial = function(fn, args) {
    const que = [];
    for(let i = 0; i < args.length; ++i)
        if(args[i] == '_')
            que.push(i);
    return function(...restArgs) {
       const res = [...args];
        for(let i = 0; i < restArgs.length; ++i)
            if(i < que.length) {
                res[que[i]] = restArgs[i];
            } else {
                res.push(restArgs[i]);
            }
        return fn(...res);
    }
};
