#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL INF = 0x7f7f7f7f7f7f7f7fLL;

int main() {
    int m;
    map<int, vector<pair<int, int> > > row, col;
    scanf("%d", &m);
    while(m--) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        if(x1 == x2) {
            row[x1].push_back({min(y1, y2), max(y1, y2)});
        } else if(y1 == y2) {
            col[y1].push_back({min(x1, x2), max(x1, x2)});
        }
    }
    int sx, sy, tx, ty;
    LL t0, t1, t2;
    scanf("%d%d%d%d%lld%lld%lld", &sx, &sy, &tx, &ty, &t0, &t1, &t2);
    t1 += t0;
    t2 += t1;
    for(auto &item: row) {
        auto &vec = item.second;
        sort(vec.begin(), vec.end());
        int tot = 0;
        for(auto &it: vec)
            if(!tot || vec[tot - 1].second < it.first) {
                vec[tot++] = it;
            } else {
                vec[tot - 1].second = max(vec[tot - 1].second, it.second);
            }
        vec.resize(tot);
        // printf("row %d: sz %d\n", item.first, tot);
    }
    for(auto &item: col) {
        auto &vec = item.second;
        sort(vec.begin(), vec.end());
        int tot = 0;
        for(auto &it: vec)
            if(!tot || vec[tot - 1].second < it.first) {
                vec[tot++] = it;
            } else {
                vec[tot - 1].second = max(vec[tot - 1].second, it.second);
            }
        vec.resize(tot);
        // printf("col %d: sz %d\n", item.first, tot);
    }
    map<int, vector<int> > rp, cp;
    map<pair<int, int>, int> idx;
    vector<pair<int, int> > seq;
    vector<vector<vector<int> > > e;
    // dir: RDLU
    auto get_idx = [&](int x, int y) {
        auto ret = idx.insert({{x, y}, (int)idx.size()});
        if(ret.second) {
            seq.push_back({x, y});
            e.push_back(vector<vector<int> >(4));
        }
        return ret.first -> second;
    };
    for(auto &rit: row)
        for(auto &rjt: rit.second)
            for(auto &cit: col)
                for(auto &cjt: cit.second) {
                    if(rit.first < cjt.first || rit.first > cjt.second)
                        continue;
                    if(cit.first < rjt.first || cit.first > rjt.second)
                        continue;
                    rp[rit.first].push_back(cit.first);
                    cp[cit.first].push_back(rit.first);
                }
    auto ins = [&](vector<int> &vec, int v) {
        auto it = lower_bound(vec.begin(), vec.end(), v);
        if(it != vec.end() && *it == v)
            return;
        int p = it - vec.begin();
        vec.push_back(v);
        rotate(vec.begin() + p, vec.end() - 1, vec.end());
    };
    ins(rp[sx], sy);
    ins(cp[sy], sx);
    ins(rp[tx], ty);
    ins(cp[ty], tx);
    for(auto &line: row) {
        int x = line.first;
        auto &p = rp[x];
        int n = p.size(), i = 0, j = 0;
        for(auto &seg: line.second) {
            for( ; i < n && p[i] < seg.first; ++i);
            if(p[i] > seg.second)
                continue;
            for(j = i + 1; j < n && p[j] <= seg.second; ++j) {
                e[get_idx(x, p[j])][2].push_back(get_idx(x, p[j - 1]));
                e[get_idx(x, p[j - 1])][0].push_back(get_idx(x, p[j]));
            }
            // if(sx == x && seg.first <= sy && sy <= seg.second) {
            //     int k = lower_bound(p.begin(), p.end(), sy) - p.begin();
            //     int pre = seg.first, suf = seg.second;
            //     if(k < n && p[k] != sy) {
            //         suf = p[k];
            //         if(i <= k && k < j)
            //             e[get_idx(sx, sy)][0].push_back(get_idx(x, p[k]));
            //     } else if(k + 1 < n && p[k] == sy) {
            //         suf = p[k + 1];
            //     }
            //     --k;
            //     if(k >= 0) {
            //         pre = p[k];
            //         if(i <= k && k < j)
            //             e[get_idx(sx, sy)][2].push_back(get_idx(x, p[k]));
            //     }
            //     if(tx == x && sy != ty && pre <= ty && ty <= suf)
            //         e[get_idx(sx, sy)][sy < ty ? 0 : 2].push_back(get_idx(tx, ty));
            // }
            // if(tx == x && seg.first <= ty && ty <= seg.second) {
            //     int k = lower_bound(p.begin(), p.end(), ty) - p.begin();
            //     if(k < n && p[k] != ty) {
            //         if(i <= k && k < j)
            //             e[get_idx(x, p[k])][2].push_back(get_idx(tx, ty));
            //     }
            //     --k;
            //     if(k >= 0) {
            //         if(i <= k && k < j)
            //             e[get_idx(x, p[k])][0].push_back(get_idx(tx, ty));
            //     }
            // }
        }
    }
    for(auto &line: col) {
        int y = line.first;
        auto &p = cp[y];
        int n = p.size(), i = 0, j = 0;
        for(auto &seg: line.second) {
            for( ; i < n && p[i] < seg.first; ++i);
            if(p[i] > seg.second)
                continue;
            for(j = i + 1; j < n && p[j] <= seg.second; ++j) {
                e[get_idx(p[j], y)][3].push_back(get_idx(p[j - 1], y));
                e[get_idx(p[j - 1], y)][1].push_back(get_idx(p[j], y));
            }
            // if(sy == y && seg.first <= sx && sx <= seg.second) {
            //     int k = lower_bound(p.begin(), p.end(), sx) - p.begin();
            //     int pre = seg.first, suf = seg.second;
            //     if(k < n && p[k] != sx) {
            //         suf = p[k];
            //         if(i <= k && k < j)
            //             e[get_idx(sx, sy)][1].push_back(get_idx(p[k], y));
            //     } else if(k + 1 < n && p[k] == sx) {
            //         suf = p[k + 1];
            //     }
            //     --k;
            //     if(k >= 0) {
            //         pre = p[k];
            //         if(i <= k && k < j)
            //             e[get_idx(sx, sy)][3].push_back(get_idx(p[k], y));
            //     }
            //     if(ty == y && sx != tx && pre <= tx && tx <= suf)
            //         e[get_idx(sx, sy)][sx < tx ? 1 : 3].push_back(get_idx(tx, ty));
            // }
            // if(ty == y && seg.first <= tx && tx <= seg.second) {
            //     int k = lower_bound(p.begin(), p.end(), tx) - p.begin();
            //     if(k < n && p[k] != tx) {
            //         if(i <= k && k < j)
            //             e[get_idx(p[k], y)][3].push_back(get_idx(tx, ty));
            //     }
            //     --k;
            //     if(k >= 0) {
            //         if(i <= k && k < j)
            //             e[get_idx(p[k], y)][1].push_back(get_idx(tx, ty));
            //     }
            // }
        }
    }
    int s = get_idx(sx, sy), t = get_idx(tx, ty), n = seq.size();
    vector<vector<bool> > vis(4, vector<bool>(n));
    vector<vector<LL> > dis(4, vector<LL>(n, INF));
    priority_queue<pair<LL, pair<int, int> > > que;
    // for(int i = 0; i < n; ++i)
    //     for(int j = 0; j < 4; ++j) {
    //         if(e[i][j].empty())
    //             continue;
    //         printf("u %d (%d %d) dir %d\n", i, seq[i].first, seq[i].second, j);
    //         for(int v: e[i][j])
    //             printf("%d ", v);
    //         puts("");
    //     }
    for(int i = 0; i < 4; ++i) {
        dis[i][s] = 0;
        que.push({-dis[i][s], {i, s}});
    }
    while(!que.empty()) {
        int ud, up;
        tie(ud, up) = que.top().second;
        que.pop();
        if(vis[ud][up])
            continue;
        vis[ud][up] = 1;
        LL udis = dis[ud][up];
        // printf("u %d (%d %d) dir %d dis %lld\n", up, seq[up].first, seq[up].second, ud, udis);
        for(int vp: e[up][ud]) {
            LL dt = abs((LL)seq[up].first - seq[vp].first) + abs((LL)seq[up].second - seq[vp].second);
            {
                int vd = ud;
                LL vdis = udis + dt;
                if(vdis % t2 < t0)
                    vdis += t0 - vdis % t2;
                if(vdis < dis[vd][vp]) {
                    dis[vd][vp] = vdis;
                    que.push({-dis[vd][vp], {vd, vp}});
                }
            }
            {
                int vd = (ud + 1) & 3;
                LL vdis = udis + dt;
                if(vdis < dis[vd][vp]) {
                    dis[vd][vp] = vdis;
                    que.push({-dis[vd][vp], {vd, vp}});
                }
            }
            {
                int vd = (ud + 3) & 3;
                LL vdis = udis + dt;
                if(vdis % t2 < t0) {
                    vdis += t0 - vdis % t2;
                } else if(vdis % t2 >= t1) {
                    vdis += t2 - vdis % t2 + t0;
                }
                if(vdis < dis[vd][vp]) {
                    dis[vd][vp] = vdis;
                    que.push({-dis[vd][vp], {vd, vp}});
                }
            }
        }
    }
    LL ans = INF;
    for(int i = 0; i < 4; ++i)
        ans = min(ans, dis[i][t]);
    printf("%lld\n", ans);
    return 0;
}
