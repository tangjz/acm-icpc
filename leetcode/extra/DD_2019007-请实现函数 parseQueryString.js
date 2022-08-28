/**
 * @param {string} url
 * @param {string} key
 * @return {string}
 */
var parseQueryString = function(url, key) {
    return new URL(url).searchParams.get(key) || '_EMPTY_';
};
