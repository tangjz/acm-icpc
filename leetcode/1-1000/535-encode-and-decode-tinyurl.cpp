class Solution {
    using u64 = unsigned long long;
    mt19937_64 rnd;
    unordered_map<u64, string> Hash;
public:
    Solution() {
        rnd.seed(19260817);
        Hash.clear();
    }

    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        u64 key;
        do key = rnd(); while(Hash.count(key));
        Hash.insert({key, longUrl});
        return to_string(key);
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        u64 key = stoull(shortUrl);
        return Hash.at(key);
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));
