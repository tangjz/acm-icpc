#include <cmath>
#include <stdio.h>
#include <cstring>
#include <algorithm>
typedef long long LL;
typedef double DB;
const int BASE = (int)1e6, maxLen = 18, maxn = 1 << maxLen | 1, maxm = (int)1e6 + 1, maxs = (int)6e5 + 1;
const DB pi = acos(-1.0);
char buf[maxs];
int kk, mod, len, seq[maxn];
int cnt, pos[maxn], tmp[maxn], elen, ex[maxn];
int tot, pr[maxm], d[maxm], pw[maxm];
int inv[maxm], fact[maxm], iact[maxm];
struct complex {
	DB r, i;
	complex() {}
	complex(DB r, DB i) : r(r), i(i) {}
	complex operator + (complex const &t) const { return complex(r + t.r, i + t.i); }
	complex operator - (complex const &t) const { return complex(r - t.r, i - t.i); }
	complex operator * (complex const &t) const { return complex(r * t.r - i * t.i, r * t.i + i * t.r); }
	complex conj() const { return complex(r, -i); }
} w[maxn], A[maxn], B[maxn], C[maxn], D[maxn];
void FFT(int n, complex a[], int flag) {
	static int bitLen = 0, bitRev[maxm];
	if(n != (1 << bitLen)) {
		for(bitLen = 0; 1 << bitLen < n; ++bitLen);
		for(int i = 1; i < n; ++i)
			bitRev[i] = (bitRev[i >> 1] >> 1) | ((i & 1) << (bitLen - 1));
	}
	for(int i = 0; i < n; ++i)
		if(i < bitRev[i])
			std::swap(a[i], a[bitRev[i]]);
	for(int i = 1, d = 1; d < n; ++i, d <<= 1)
		for(int j = 0; j < n; j += d << 1)
			for(int k = 0; k < d; ++k) {
				complex &AL = a[j + k], &AH = a[j + k + d], TP = w[k << (maxLen - i)] * AH;
				AH = AL - TP;
				AL = AL + TP;
			}
	if(flag != -1)
		return;
	std::reverse(a + 1, a + n);
	for(int i = 0; i < n; ++i) {
		 a[i].r /= n;
		 a[i].i /= n;
	}
}
int mod_pow(int x, int k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		(k & 1) && (ret = (LL)ret * x % mod);
	return ret;
}
int main() {
	scanf("%s", buf);
	int slen = strlen(buf);
	len = (slen - 1) / 6 + 1;
	for(int i = 0; i < len; ++i) {
		int R = slen - i * 6, L = std::max(R - 6, 0);
		buf[R] = '\0';
		sscanf(buf + L, "%d", seq + i);
	}
	scanf("%s%d", buf, &mod); // mod <= 1e6
	if(mod == 2) {
		puts("0");
		return 0;
	}
	for(int i = 0; buf[i]; ++i)
		kk = ((kk << 3) + (kk << 1) + (buf[i] - '0')) % (mod - 1);
	for(int i = 0, ilim = 1 << maxLen; i < ilim; ++i) {
		int j = i, k = ilim >> 1;
		for( ; !(j & 1) && !(k & 1); j >>= 1, k >>= 1);
		w[i] = complex(cos(pi / k * j), sin(pi / k * j));
	}
	int sp, msk;
	for(sp = 1; 1 << (sp << 1) < mod; ++sp);
	msk = (1 << sp) - 1;
	memcpy(ex, seq, len * sizeof(int));
	cnt = len;
	int ctr = 0;
	for(int i = 0; i < len; ++i) {
		pos[i] = ctr;
		for(int val = ex[i]; val > 0; val /= mod)
			seq[ctr++] = val % mod;
	}
	pos[cnt] = ctr;
	len = ctr;
	elen = 0;
	for(int val = BASE; val > 0; val /= mod)
		ex[elen++] = val % mod;
	complex trL(0.5, 0), trH(0, -0.5), tr(0, 1);
	while(cnt > 1) {
		int size;
		for(size = 1; size < (elen << 1) - 1; size <<= 1);
		for(int i = 1; i < cnt; i += 2)
			for(int j = elen + pos[i + 1] - pos[i] - 1; size < j; size <<= 1);
		for(int i = 0; i < size; ++i)
			A[i] = i < elen ? complex(ex[i] & msk, ex[i] >> sp) : complex(0, 0);
		FFT(size, A, 1);
		memcpy(tmp, seq, len * sizeof(int));
		int ctr = 0;
		for(int i = 0; i < cnt; i += 2) {
			int L = pos[i], M = pos[i + 1];
			pos[i >> 1] = ctr;
			if(i + 1 < cnt) {
				int R = pos[i + 2], *vec = tmp + M;
				for(int j = 0; j < size; ++j)
					B[j] = M + j < R ? complex(vec[j] & msk, vec[j] >> sp) : complex(0, 0);
				FFT(size, B, 1);
				for(int j = 0; j < size; ++j) {
					int k = (size - j) & (size - 1);
					complex AL = (A[j] + A[k].conj()) * trL;
					complex AH = (A[j] - A[k].conj()) * trH;
					complex BL = (B[j] + B[k].conj()) * trL;
					complex BH = (B[j] - B[k].conj()) * trH;
					C[j] = AL * (BL + BH * tr);
					D[j] = AH * (BL + BH * tr);
				}
				FFT(size, C, -1);
				FFT(size, D, -1);
				int tlen = std::max(M - L, elen + R - M - 1), *v1 = tmp + L, *v2 = seq + ctr;
				LL rem = 0;
				for(int j = 0; j < tlen; ++j) {
					if(L + j < M)
						rem += v1[j];
					if(j < size) {
						LL v11 = C[j].r + 0.5, v12 = C[j].i + 0.5;
						LL v21 = D[j].r + 0.5, v22 = D[j].i + 0.5;
						rem += (((v22 << sp) + v12 + v21) << sp) + v11;
					}
					v2[j] = rem % mod;
					rem /= mod;
				}
				for( ; rem > 0; rem /= mod)
					v2[tlen++] = rem % mod;
				for( ; tlen > 1 && !v2[tlen - 1]; --tlen);
				ctr += tlen;
			} else {
				memcpy(seq + ctr, tmp + L, (M - L) * sizeof(int));
				ctr += M - L;
			}
		}
		cnt = (cnt + 1) >> 1;
		len = pos[cnt] = ctr;
		if(cnt > 1) {
			for(int i = 0; i < size; ++i) {
				int j = (size - i) & (size - 1);
				complex AL = (A[i] + A[j].conj()) * trL;
				complex AH = (A[i] - A[j].conj()) * trH;
				C[i] = AL * (AL + AH * tr);
				D[i] = AH * (AL + AH * tr);
			}
			FFT(size, C, -1);
			FFT(size, D, -1);
			elen = size;
			LL rem = 0;
			for(int i = 0; i < elen; ++i) {
				LL v11 = C[i].r + 0.5, v12 = C[i].i + 0.5;
				LL v21 = D[i].r + 0.5, v22 = D[i].i + 0.5;
				rem += (((v22 << sp) + v12 + v21) << sp) + v11;
				ex[i] = rem % mod;
				rem /= mod;
			}
			for( ; rem > 0; rem /= mod)
				ex[elen++] = rem % mod;
			for( ; elen > 1 && !ex[elen - 1]; --elen);
		}
	}
	pw[1] = inv[1] = fact[0] = fact[1] = iact[0] = iact[1] = 1;
	for(int i = 2; i < mod; ++i) {
		if(!d[i]) {
			pr[tot++] = d[i] = i;
			pw[i] = mod_pow(i, kk);
		}
		for(int j = 0, k; (k = i * pr[j]) < mod; ++j) {
			d[k] = pr[j];
			pw[k] = (LL)pw[i] * pw[pr[j]] % mod;
			if(d[i] == pr[j])
				break;
		}
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * inv[i] % mod;
	}
	int ans = 1;
	for(int i = 1; i < len; ++i) {
		if(seq[i] & 1) {
			ans = 0;
			break;
		}
		ans = (LL)ans * fact[seq[i]] * iact[seq[i] >> 1] % mod * iact[seq[i] >> 1] % mod;
	}
	if(!ans) {
		puts("0");
		return 0;
	}
	int lim = seq[0], coeff = 1, sum = pw[lim];
	for(int i = 1, j = lim - 1; i < j; ++i, --j) {
		coeff = coeff * (j + 1LL) * inv[i] % mod;
		sum = (sum + (pw[j] - pw[i]) * (LL)coeff) % mod;
	}
	ans = (LL)ans * (sum << 1) % mod;
	printf("%d\n", ans < 0 ? ans + mod : ans);
	return 0;
}
