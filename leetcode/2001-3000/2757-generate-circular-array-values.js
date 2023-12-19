/**
 * @param {Array<number>} arr
 * @param {number} startIndex
 * @yields {number}
 */
var cycleGenerator = function* (arr, idx) {
    while (true) {
        let ret = yield arr[idx];
        idx = (idx + ret) % arr.length;
        if (idx < 0)
            idx += arr.length;
    }
};

/**
 *  const gen = cycleGenerator([1,2,3,4,5], 0);
 *  gen.next().value  // 1
 *  gen.next(1).value // 2
 *  gen.next(2).value // 4
 *  gen.next(6).value // 5
 */
