/**
 * This is the interface for the expression tree Node.
 * You should not remove it, and you can define some classes to implement it.
 */

class Node {
public:
    virtual ~Node () {};
    virtual int evaluate() const = 0;
protected:
    // define your fields here
};

class NumNode: public Node {
    int val;
public:
    NumNode(int val = 0) : val(val) {}
    int evaluate() const {
        return val;
    }
};

class OpNode: public Node {
    char typ;
    Node *lft, *rht;
public:
    OpNode(char typ, Node *lft, Node *rht) : typ(typ), lft(lft), rht(rht) {}
    int evaluate() const {
        int vL = lft -> evaluate(), vR = rht -> evaluate();
        switch(typ) {
            case '+': return vL + vR;
            case '-': return vL - vR;
            case '*': return vL * vR;
            case '/': return vL / vR;
        }
        return 0;
    }
};


/**
 * This is the TreeBuilder class.
 * You can treat it as the driver code that takes the postinfix input
 * and returns the expression tree represnting it as a Node.
 */

class TreeBuilder {
public:
    Node* buildTree(vector<string>& postfix) {
        stack<Node *> stk;
        for(auto &it: postfix)
            if(it.back() >= '0' && it.back() <= '9') {
                stk.push(new NumNode(stoi(it)));
            } else {
                Node *rht = stk.top();
                stk.pop();
                Node *lft = stk.top();
                stk.pop();
                stk.push(new OpNode(it.back(), lft, rht));
            }
        return stk.top();
    }
};


/**
 * Your TreeBuilder object will be instantiated and called as such:
 * TreeBuilder* obj = new TreeBuilder();
 * Node* expTree = obj->buildTree(postfix);
 * int ans = expTree->evaluate();
 */
