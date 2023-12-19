/**
 * @param {number} rowsCount
 * @param {number} colsCount
 * @return {Array<Array<number>>}
 */
Array.prototype.snail = function (rowsCount, colsCount) {
    if (this.length != rowsCount * colsCount)
        return [];
    const ret = new Array(rowsCount).fill(0).map(_ => new Array(colsCount).fill(0));
    for (let i = 0, k = 0; i < colsCount; ++i) {
        var ofs = 0, inc = 1;
        if (i & 1) {
            ofs = rowsCount - 1;
            inc = -inc;
        }
        for (let j = 0; j < rowsCount; ++j, ++k, ofs += inc)
            ret[ofs][i] = this[k];
    }
    return ret;
}

/**
 * const arr = [1,2,3,4];
 * arr.snail(1,4); // [[1,2,3,4]]
 */
