class EventEmitter {
    constructor() {
        this.relations = new Map();
    }

    /**
     * @param {string} eventName
     * @param {Function} callback
     * @return {Object}
     */
    subscribe(eventName, callback) {
        const callbacks = this.relations.get(eventName) ?? [];
        callbacks.push(callback);
        this.relations.set(eventName, callbacks);
        return {
            unsubscribe: () => {
                const callbacks = (this.relations.get(eventName) ?? []).filter(fn => fn !== callback);
                this.relations.set(eventName, callbacks);
            }
        };
    }

    /**
     * @param {string} eventName
     * @param {Array} args
     * @return {Array}
     */
    emit(eventName, args = []) {
        const callbacks = this.relations.get(eventName) ?? [];
        const res = [];
        for (const cb of callbacks)
            res.push(cb(...args));
        return res;
    }
}

/**
 * const emitter = new EventEmitter();
 *
 * // Subscribe to the onClick event with onClickCallback
 * function onClickCallback() { return 99 }
 * const sub = emitter.subscribe('onClick', onClickCallback);
 *
 * emitter.emit('onClick'); // [99]
 * sub.unsubscribe(); // undefined
 * emitter.emit('onClick'); // []
 */
