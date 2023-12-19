/**
 * @param {string} start
 * @param {string} end
 * @param {number} step
 * @yields {string}
 */
var dateRangeGenerator = function* (start, end, step) {
    let staTime = new Date(start).getTime();
    const endTime = new Date(end).getTime();
    const strip = step * 24 * 60 * 60 * 1000;
    while (staTime <= endTime) {
        yield new Date(staTime).toISOString().split('T')[0];
        staTime += strip;
    }
};

/**
 * const g = dateRangeGenerator('2023-04-01', '2023-04-04', 1);
 * g.next().value; // '2023-04-01'
 * g.next().value; // '2023-04-02'
 * g.next().value; // '2023-04-03'
 * g.next().value; // '2023-04-04'
 * g.next().done; // true
 */
