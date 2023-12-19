/**
 * @param {number} target
 * @return {number}
 */
Array.prototype.upperBound = function (target) {
    let L = 0, R = this.length - 1;
    while (L < R) {
        let M = (L + R + 1) >> 1;
        if (this[M] <= target) {
            L = M;
        } else {
            R = M - 1;
        }
    }
    return this[L] == target ? L : -1;
};


// [3,4,5].upperBound(5); // 2
// [1,4,5].upperBound(2); // -1
// [3,4,6,6,6,6,7].upperBound(6) // 5
