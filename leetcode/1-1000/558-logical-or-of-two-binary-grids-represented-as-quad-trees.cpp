/*
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;
    
    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/

class Solution {
public:
    Node* intersect(Node* quadTree1, Node* quadTree2) {
        if(quadTree1 == nullptr)
            return nullptr;
        bool hasLeaf = false, val = false;
        if(quadTree1 -> isLeaf) {
            hasLeaf = true;
            val |= quadTree1 -> val;
        }
        if(quadTree2 -> isLeaf) {
            hasLeaf = true;
            val |= quadTree2 -> val;
        }
        if(hasLeaf) {
           if(val)
               return quadTree1 -> isLeaf && quadTree1 -> val ? quadTree1 : quadTree2;
            return quadTree1 -> isLeaf && !(quadTree1 -> val) ? quadTree2 : quadTree1;
        }
        int cnt[2] = {};
        quadTree1 -> topLeft = intersect(quadTree1 -> topLeft, quadTree2 -> topLeft);
        if(quadTree1 -> topLeft -> isLeaf)
            ++cnt[quadTree1 -> topLeft -> val];
        quadTree1 -> topRight = intersect(quadTree1 -> topRight, quadTree2 -> topRight);
        if(quadTree1 -> topRight -> isLeaf)
            ++cnt[quadTree1 -> topRight -> val];
        quadTree1 -> bottomLeft = intersect(quadTree1 -> bottomLeft, quadTree2 -> bottomLeft);
        if(quadTree1 -> bottomLeft -> isLeaf)
            ++cnt[quadTree1 -> bottomLeft -> val];
        quadTree1 -> bottomRight = intersect(quadTree1 -> bottomRight, quadTree2 -> bottomRight);
        if(quadTree1 -> bottomRight -> isLeaf)
            ++cnt[quadTree1 -> bottomRight -> val];
        if(max(cnt[0], cnt[1]) == 4) {
            quadTree1 -> isLeaf = true;
            quadTree1 -> val = cnt[1] == 4;
            quadTree1 -> topLeft = quadTree1 -> topRight = quadTree1 -> bottomLeft = quadTree1 -> bottomRight = nullptr;
        }
        return quadTree1;
    }
};
