/**
 * @param {Object | Array} obj
 * @return {Object | Array} immutable obj
 */
var makeImmutable = function(obj) {
    const keyBarrier = { set: (_, k) => { throw `Error Modifying: ${k}` } };
    const idxBarrier = { set: (_, i) => { throw `Error Modifying Index: ${i}` } };
    const callBarrier = { apply: (func) => { throw `Error Calling Method: ${func.name}` } };
    const callers = ['pop', 'push', 'shift', 'unshift', 'splice', 'sort', 'reverse'];
    const wrapper = (obj) => {
        for(let p in obj) {
            if(typeof obj[p] === 'object' && obj[p] !== null) {
                obj[p] = wrapper(obj[p]);
            }
        }
        if(Array.isArray(obj)) {
            callers.forEach(fn => { obj[fn] = new Proxy(obj[fn], callBarrier) });
            return new Proxy(obj, idxBarrier);
        }
        return new Proxy(obj, keyBarrier);
    };
    return wrapper(obj);
};

/**
 * const obj = makeImmutable({x: 5});
 * obj.x = 6; // throws "Error Modifying x"
 */