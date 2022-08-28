var Sub = function(initValue) {
// 请在此处编写你的代码，其他部分请勿修改，否则不记分。
// begin
    let val = initValue || 0;
    this.add = (adt) => {
        if(typeof adt == 'number')
            val += adt;
        return this;
    };
    this.getResult = () => val;
// end
};
