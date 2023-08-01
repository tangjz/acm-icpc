var ImmutableHelper = function(obj) {
    this._base = obj;
};

/** 
 * @param {Function} mutator
 * @return {JSON} clone of obj
 */
ImmutableHelper.prototype.produce = function(mutator) {
    const wrapper = (obj, diff) => {
        return new Proxy(obj, {
            set: (_, p, v) => {
                diff[p] = v;
            },
            get: (tgt, p) => {
                if(typeof obj[p] === 'object' && obj[p] !== null) {
                    if(diff[p] === undefined) {
                        diff[p] = {};
                    }
                    return wrapper(obj[p], diff[p]);
                }
                return diff[p] === undefined ? Reflect.get(tgt, p) : diff[p];
            }
        });
    };
    const diff = {};
    const res = wrapper(this._base, diff);
    mutator(res);
    // return { ...res, ...diff };
    return diff;
};

/**
 * const originalObj = {"x": 5};
 * const mutator = new ImmutableHelper(originalObj);
 * const newObj = mutator.produce((proxy) => {
 *   proxy.x = proxy.x + 1;
 * });
 * console.log(originalObj); // {"x: 5"}
 * console.log(newObj); // {"x": 6}
 */