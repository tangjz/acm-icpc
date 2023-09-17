var ImmutableHelper = function(obj) {
    this.obj = obj;
};

/**
 * @param {Function} mutator
 * @return {JSON} clone of obj
 */
ImmutableHelper.prototype.produce = function(mutator) {
    const isObj = o => typeof o === 'object' && o !== null;
    const wrapper = (obj, diff) => {
        return new Proxy(obj, {
              set(_, p, v) {
                  diff[p] = v;
              },
              get(_, p) {
                  if(!(p in diff)) {
                      diff[p] = {};
                  }
                  if(!isObj(diff[p])) {
                      return diff[p];
                  }
                  if(isObj(obj[p])) {
                      return wrapper(obj[p], diff[p]);
                  }
                  return obj[p];
              },
        });
    };
    const purify = (diff) => {
        if(!isObj(diff)) {
            return true;
        }
        let upd = false;
        for(const key in diff) {
            if(!purify(diff[key])) {
                delete diff[key];
            } else {
                upd = true;
            }
        }
        return upd;
    };
    const reduce = (obj, diff) => {
        if(!isObj(diff)) {
            return diff;
        }
        let res = { ...obj };
        for(const key in diff) {
            res[key] = reduce(obj[key], diff[key]);
        }
        return res;
    };
    const diff = {};
    const proxy = wrapper(this.obj, diff);
    mutator(proxy);
    return purify(diff) ? reduce(this.obj, diff) : this.obj;
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
