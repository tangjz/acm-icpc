#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <set>
#include <utility>
using namespace std;
const int oo = ~0U>>1;
set<pair<int,int> > segs;
int n,x,p;

int main(){
    scanf("%d",&n);
    set<pair<int,int> >::iterator it,prec,succ;
    for(int i = 0;i < n;++ i){
        scanf("%d",&x);
        if(x > 0){
            scanf("%d",&p);
            succ = segs.upper_bound(make_pair(x,oo));
            prec = succ;
            int la,lb,ra,rb,retl = x,retr = x + p - 1;
            if(!segs.empty() && prec != segs.begin()){
                -- prec;
                la = (*prec).first; lb = (*prec).second;
                /*
                if(i == n - 1)
                    printf("la:lb = %d %d\n",la,lb);
                */
                if(x <= lb + 1){
                    retl = la;
                    x = lb + 1;
                    segs.erase(prec);
                }
            }
            retr = x + p - 1;
            if(succ != segs.end()){
                ra = (*succ).first; rb = (*succ).second;
                if(x + p >= ra){
                    p = ra - x;
                    retr = rb;
                    segs.erase(succ);
                }
            }
            segs.insert(make_pair(retl,retr));
            printf("%d %d\n",x,x + p - 1);
            /*
            printf("retl,retr : %d %d\n",retl,retr);
            */
        }else{
            x = -x;
            succ = segs.upper_bound(make_pair(x,oo));
            prec = succ;
            if(!segs.empty() && prec != segs.begin()){
                -- prec;
                int la,lb;
                /*
                printf("%d\n",prec->second);
                */
                if((lb = (*prec).second) >= x){
                    la = (*prec).first;
                    segs.erase(prec);
                    if(la < x)
                        segs.insert(make_pair(la,x - 1));
                    if(lb > x)
                        segs.insert(make_pair(x + 1,lb));
                    /*
                    puts("Real Del");
                    */
                }
            }
        }
    }
    return 0;
}
