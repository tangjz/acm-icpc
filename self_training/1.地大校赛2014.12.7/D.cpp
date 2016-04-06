#include <cstdio>
#include <cstring>
const char *tran = "(fnm:qeb)jcr,[<*ak>+3g.d1-?h^i_=", *pos = "abcdefghijklmnopqrstuvwxyz ,.\'!?", *unuse = "stuvwxyz{|}~!#";
char tem[2333] = "\
     #include      <stdio.h>\n\
   main(t ,_,a)  char*a;{return\n\
 t<1?main(*a,a[-t],\"=a-1kj3gnm:q\\\n\
ebh_cf*<r.d>i^+?,()[?qzyrjuvcdefg\\\n\
h,!kbpolwxs'.t main(\")&&a[-t]&&main\n\
(t-1,_,a):t/2?_==*a?putchar(32[a])\n\
  :_%115<36||main(t,_,a+1):main(\n\
    0,t,\"````````````````````\\\n\
      `````````````````````\\\n\
        `````````````````\\\n\
          `````````````\\\n\
            `````````\\\n\
              ````\")\n\
                ;}";
char str[100], out[2333];
char trans(char x)
{
	for(int i = 0; pos[i] != '\0'; ++i)
		if(x == pos[i])
			return tran[i];
	return unuse[0];
}
int main()
{
	gets(str);
	for(int i = 0; i < 84; ++i)
		str[i] = trans(str[i]);
	memcpy(out, tem, sizeof tem);
	for(int i = 0, j = 0; out[i] != '\0'; ++i)
		if(out[i] == '`')
			out[i] = str[j++];
	printf("%s", out);
	return 0;
}
