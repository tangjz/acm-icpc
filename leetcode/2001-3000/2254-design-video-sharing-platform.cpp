class VideoSharingPlatform {
    vector<string> seq;
    vector<int> ctr[3];
    priority_queue<int> cand;
public:
    VideoSharingPlatform() {
    }
    
    int upload(string video) {
        int videoId;
        if(cand.empty()) {
            videoId = seq.size();
            seq.push_back("");
            ctr[0].push_back(0);
            ctr[1].push_back(0);
            ctr[2].push_back(0);
        } else {
            videoId = -cand.top();
            cand.pop();
        }
        seq[videoId] = move(video);
        return videoId;
    }
    
    void remove(int videoId) {
        if(videoId < seq.size() && !seq[videoId].empty()) {
            seq[videoId] = "";
            ctr[0][videoId] = ctr[1][videoId] = ctr[2][videoId] = 0;
            cand.push(-videoId);
        }
    }
    
    string watch(int videoId, int startMinute, int endMinute) {
        if(videoId >= seq.size() || seq[videoId].empty())
            return "-1";
        ++ctr[0][videoId];
        return seq[videoId].substr(startMinute, min(endMinute + 1, (int)seq[videoId].size()) - startMinute);
    }
    
    void like(int videoId) {
        if(videoId < seq.size() && !seq[videoId].empty())
            ++ctr[1][videoId];
    }
    
    void dislike(int videoId) {
        if(videoId < seq.size() && !seq[videoId].empty())
            ++ctr[2][videoId];
    }
    
    vector<int> getLikesAndDislikes(int videoId) {
        if(videoId >= seq.size() || seq[videoId].empty())
            return {-1};
        return {ctr[1][videoId], ctr[2][videoId]};
    }
    
    int getViews(int videoId) {
        if(videoId >= seq.size() || seq[videoId].empty())
            return -1;
        return ctr[0][videoId];
    }
};

/**
 * Your VideoSharingPlatform object will be instantiated and called as such:
 * VideoSharingPlatform* obj = new VideoSharingPlatform();
 * int param_1 = obj->upload(video);
 * obj->remove(videoId);
 * string param_3 = obj->watch(videoId,startMinute,endMinute);
 * obj->like(videoId);
 * obj->dislike(videoId);
 * vector<int> param_6 = obj->getLikesAndDislikes(videoId);
 * int param_7 = obj->getViews(videoId);
 */
