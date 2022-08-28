#include <cctype>
class Solution {
	struct Compare {
		bool operator() (vector<string> const &u, vector<string> const &v) const {
			if(u.size() != v.size())
				return u.size() > v.size();
			for(int i = 0; i < (int)u.size(); ++i)
				if(u[i] != v[i])
					return u[i] < v[i];
			return 0;
		}
	};
    typedef map<vector<string>, int, Compare> Terms;
    Terms parseTerm(int &pos, string &expression, vector<string> &evalvars, vector<int> &evalints) {
        Terms ret;
        while(pos < (int)expression.length() && expression[pos] == ' ')
            ++pos;
        if(expression[pos] == '(') {
            ret = parseExpression(++pos, expression, evalvars, evalints);
            assert(expression[pos] == ')');
            ++pos;
        } else if(isalpha(expression[pos])) {
            int sta = pos;
            while(pos < (int)expression.length() && isalpha(expression[pos]))
                ++pos;
            string tmp = expression.substr(sta, pos - sta), sym = tmp;
            int val = 1;
            for(int i = 0; i < (int)evalvars.size(); ++i)
                if(tmp == evalvars[i]) {
                    sym = "";
                    val = evalints[i];
                    break;
                }
            if(val) {
                vector<string> vec;
                if(sym != "")
                    vec.push_back(sym);
                ret[vec] += val;
            }
        } else if(isdigit(expression[pos])) {
            int sta = pos;
            while(pos < (int)expression.length() && isdigit(expression[pos]))
                ++pos;
            int val = stoi(expression.substr(sta, pos - sta));
            if(val)
                ret[vector<string>()] += val;
        } else {
            assert(0);
        }
        return ret;
    }
    Terms parseExpression(int &pos, string &expression, vector<string> &evalvars, vector<int> &evalints) {
        stack<Terms> stk;
        stk.push(parseTerm(pos, expression, evalvars, evalints));
        while(pos < (int)expression.length())
            if(expression[pos] == ' ') {
                ++pos;
            } else if(expression[pos] == ')') {
                break;
            } else if(expression[pos] == '+' || expression[pos] == '-') {
                int sgn = expression[pos] == '+' ? 1 : -1;
                Terms tmp = parseTerm(++pos, expression, evalvars, evalints);
                for(auto &it : tmp)
                    tmp[it.first] = sgn * it.second;
                stk.push(tmp);
            } else if(expression[pos] == '*') {
                Terms cur = stk.top(), tmp = parseTerm(++pos, expression, evalvars, evalints), nxt;
                stk.pop();
                for(auto &it : cur)
                    for(auto &jt : tmp) {
                        vector<string> vec;
                        for(auto &buf : it.first)
                        	vec.push_back(buf);
                        for(auto &buf : jt.first)
                        	vec.push_back(buf);
                        sort(vec.begin(), vec.end());
                        nxt[vec] += it.second * jt.second;
                    }
                stk.push(nxt);
            } else {
                assert(0);
            }
        Terms ret;
        while(!stk.empty()) {
            Terms cur = stk.top();
            stk.pop();
            for(auto &it : cur)
                ret[it.first] += it.second;
        }
        for(auto it : ret)
            if(!it.second)
                ret.erase(it.first);
        return ret;
    }
public:
    vector<string> basicCalculatorIV(string expression, vector<string> &evalvars, vector<int> &evalints) {
        int pos = 0;
        Terms result = parseExpression(pos, expression, evalvars, evalints);
        assert(pos == (int)expression.length());
        vector<string> answer;
        for(auto &it : result) {
            if(!it.second)
                continue;
            string buf = to_string(it.second);
            for(auto &jt : it.first)
                buf += '*' + jt;
            answer.push_back(buf);
        }
        return answer;
    }
};
