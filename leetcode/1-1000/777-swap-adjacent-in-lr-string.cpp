class Solution {
public:
    bool canTransform(string start, string end) {
        while(!start.empty() || !end.empty()) {
            while(!start.empty() && start.back() == 'X')
                start.pop_back();
            while(!end.empty() && end.back() == 'X')
                end.pop_back();
            if(start.empty() != end.empty())
                return 0;
            if(start.empty())
                break;
            if(start.back() != end.back())
                return 0;
            if(start.back() == 'L' && start.size() < end.size())
                return 0;
            if(start.back() == 'R' && start.size() > end.size())
                return 0;
            start.pop_back();
            end.pop_back();
        }
        return 1;
    }
};
