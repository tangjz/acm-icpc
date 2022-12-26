/**
 * // This is the HtmlParser's API interface.
 * // You should not implement it, or speculate about its implementation
 * class HtmlParser {
 *   public:
 *     vector<string> getUrls(string url);
 * };
 */
class Solution {
    mutex m;
    condition_variable cv;
    string hostName;
    vector<thread> pool;
    vector<string> que;
    unordered_set<string> sp;
    int done, active;

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
        pool.clear();
        que.clear();
        sp.clear();
        done = active = 0;

        hostName = getHostName(startUrl);
        extend(startUrl);

        auto worker = [&]() {
            while(true) {
                string url;
                {
                    auto ul = unique_lock(m);
                    cv.wait(ul, [&]() {
                        return done < (int)que.size() || !active;
                    });
                    if(done == (int)que.size())
                        break;
                    url = que[done++];
                    ++active;
                }
                vector<string> cand;
                for(auto &it: htmlParser.getUrls(url))
                    if(getHostName(it) == hostName)
                        cand.push_back(it);
                {
                    auto ul = unique_lock(m);
                    --active;
                    for(auto &it: cand)
                        extend(it);
                }
                cv.notify_all();
            }
        } ;
        for(int i = 1; i < (int)thread::hardware_concurrency(); ++i)
            pool.emplace_back(worker);
        worker();
        for(auto &it: pool)
            it.join();
        return que;
    }
};
