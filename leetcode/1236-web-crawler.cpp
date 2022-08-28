/**
 * // This is the HtmlParser's API interface.
 * // You should not implement it, or speculate about its implementation
 * class HtmlParser {
 *   public:
 *     vector<string> getUrls(string url);
 * };
 */

class Solution {
    string hostName;
    vector<string> que;
    unordered_set<string> sp;
    
    string getHostName(string const &s) {
        auto pos = s.find('/', 7);
        return s.substr(7, pos == string::npos ? pos : pos - 7);
    }
    
    void extend(string const &s) {
        if(getHostName(s) == hostName && sp.insert(s).second) {
            que.push_back(string(s));
        }
    }
public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        que.clear();
        sp.clear();
        hostName = getHostName(startUrl);
        extend(startUrl);
        for(int i = 0; i < que.size(); ++i) {
            string url = que[i];
            for(auto &it: htmlParser.getUrls(url))
                if(getHostName(it) == hostName)
                    extend(it);
        }
        return que;
    }
};
