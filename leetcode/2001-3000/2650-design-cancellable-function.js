/**
 * @param {Generator} generator
 * @return {[Function, Promise]}
 */
var cancellable = function(generator) {
    let cancel;
    const p1 = new Promise((_, reject) => {
        cancel = () => reject("Cancelled");
    });
    p1.catch(() => {});
    const p2 = (async () => {
        let result = {
            'value': async () => undefined,
            'done': false,
        };
        while(!result.done) {
            try {
                result = generator.next(await Promise.race([result.value, p1]));
            } catch(e) {
                result = generator.throw(e);
            }
        }
        return result.value;
    })();
    return [cancel, p2];
};

/**
 * function* tasks() {
 *   const val = yield new Promise(resolve => resolve(2 + 2));
 *   yield new Promise(resolve => setTimeout(resolve, 100));
 *   return val + 1;
 * }
 * const [cancel, promise] = cancellable(tasks());
 * setTimeout(cancel, 50);
 * promise.catch(console.log); // logs "Cancelled" at t=50ms
 */
