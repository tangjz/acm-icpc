/**
 * @return {Object}
 */
var createInfiniteObject = function() {
    return new Proxy({}, { get: (_, k) => () => k } );
};

/**
 * const obj = createInfiniteObject();
 * obj['abc123'](); // "abc123"
 */
