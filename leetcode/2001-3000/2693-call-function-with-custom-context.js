/**
 * @param {Object} context
 * @param {Array} args
 * @return {null|boolean|number|string|Array|Object}
 */
Function.prototype.callPolyfill = function (context, ...args) {
    const ctx = { ...context };
    ctx.__proto__.func = this;
    return ctx.func(...args);
}

/**
 * function increment() { this.count++; return this.count; }
 * increment.callPolyfill({count: 1}); // 2
 */
