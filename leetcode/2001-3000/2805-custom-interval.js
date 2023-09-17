/**
 * @param {Function} fn
 * @param {number} delay
 * @param {number} period
 * @return {number} id
 */

const timeQue = [];

function customInterval(fn, delay, period){
    let idx = timeQue.length, cnt = 0;
    const exec = () => {
        fn();
        cnt += period;
        timeQue[idx] = setTimeout(exec, delay + cnt);
    };
    timeQue.push(setTimeout(exec, delay + cnt));
    return idx;
}

/**
 * @param {number} id
 */
function customClearInterval(id) {
    clearTimeout(timeQue[id]);
}
