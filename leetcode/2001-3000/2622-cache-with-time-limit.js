var TimeLimitedCache = function() {
    this.cache = new Map();
};

/**
 * @param {number} key
 * @param {number} value
 * @param {number} time until expiration in ms
 * @return {boolean} if un-expired key already existed
 */
TimeLimitedCache.prototype.set = function(key, value, duration) {
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
TimeLimitedCache.prototype.get = function(key) {
    var val = this.cache.get(key)?.val;
    return val === undefined ? -1 : val;
};

/**
 * @return {number} count of non-expired keys
 */
TimeLimitedCache.prototype.count = function() {
    return this.cache.size;
};

/**
 * Your TimeLimitedCache object will be instantiated and called as such:
 * var obj = new TimeLimitedCache()
 * obj.set(1, 42, 1000); // false
 * obj.get(1) // 42
 * obj.count() // 1
 */
