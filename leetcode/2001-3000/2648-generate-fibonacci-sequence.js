/**
 * @return {Generator<number>}
 */
var fibGenerator = function*() {
    let a = 1, b = 0;
    while(true) {
        yield b;
        [a, b] = [b, a + b];
    }
};

/**
 * const gen = fibGenerator();
 * gen.next().value; // 0
 * gen.next().value; // 1
 */
