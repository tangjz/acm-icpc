class EventEmitter {
    constructor() {
        this.relations = new Map();
    }

    subscribe(event, cb) {
        const callbacks = this.relations.get(event) ?? [];
        callbacks.push(cb);
        this.relations.set(event, callbacks);
        return {
            unsubscribe: () => {
                const callbacks = (this.relations.get(event) ?? []).filter(fn => fn !== cb);
                this.relations.set(event, callbacks);
            }
        };
    }

    emit(event, args = []) {
        const callbacks = this.relations.get(event) ?? [];
        const res = [];
        for(const cb of callbacks)
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
