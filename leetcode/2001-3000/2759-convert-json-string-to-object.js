/**
 * @param {string} str
 * @return {*}
 */
var jsonParse = function(str) {
    let idx = 0;
    const parseObj = () => {
        const res = {};
        for(++idx; str[idx] !== '}'; ++idx) {
            const key = parseStr();
            ++idx;
            const val = parseVal();
            res[key] = val;
            if(str[idx] === '}')
                break;
        }
        ++idx;
        return res;
    };
    const parseArr = () => {
        const res = [];
        for(++idx; str[idx] !== ']'; ++idx) {
            const val = parseVal();
            res.push(val);
            if(str[idx] === ']')
                break;
        }
        ++idx;
        return res;
    };
    const parseStr = () => {
        ++idx;
        const end = str.indexOf('"', idx);
        const val = str.slice(idx, end);
        idx = end + 1;
        return val;
    };
    const parseNum = () => {
        let end = idx;
        if(str[end] === '-')
            ++end;
        for( ; str[end] >= '0' && str[end] <= '9'; ++end);
        if(str[end] === '.')
            ++end;
        for( ; str[end] >= '0' && str[end] <= '9'; ++end);
        const val = Number(str.slice(idx, end));
        idx = end;
        return val;
    };
    const parseVal = () => {
        switch(str[idx]) {
        case '{': return parseObj();
        case '[': return parseArr();
        case '"': return parseStr();
        case 't': {
            idx += 4;
            return true;
        }
        case 'f': {
            idx += 5;
            return false;
        }
        case 'n': {
            idx += 4;
            return null;
        }
        default: return parseNum();
        }
    };
    return parseVal();
};
