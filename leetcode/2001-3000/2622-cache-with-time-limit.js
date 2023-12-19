var TimeLimitedCache = function () {
    this.cache = new Map();
};

/**
 * @param {number} key
 * @param {number} value
 * @param {number} duration time until expiration in ms
 * @return {boolean} if un-expired key already existed
 */
TimeLimitedCache.prototype.set = function (key, value, duration) {
    var cur = this.cache.get(key);
    clearTimeout(cur?.clean);
    this.cache.set(key, {
        'val': value,
        'clean': setTimeout(() => this.cache.delete(key), duration),
    });
    return cur !== undefined;
};

/**
 * @param {number} key
 * @return {number} value associated with key
 */
TimeLimitedCache.prototype.get = function (key) {
    var val = this.cache.get(key)?.val;
    return val === undefined ? -1 : val;
};

/**
 * @return {number} count of non-expired keys
 */
TimeLimitedCache.prototype.count = function () {
    return this.cache.size;
};

/**
 * const timeLimitedCache = new TimeLimitedCache()
 * timeLimitedCache.set(1, 42, 1000); // false
 * timeLimitedCache.get(1) // 42
 * timeLimitedCache.count() // 1
 */
