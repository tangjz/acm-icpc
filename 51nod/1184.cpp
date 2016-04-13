#include <cstdio>
typedef long long LL;
const LL ans[1001] = {1,15485863,32452843,49979687,67867967,86028121,104395301,122949823,141650939,160481183,179424673,198491317,217645177,236887691,256203161,275604541,295075147,314606869,334214459,353868013,373587883,393342739,413158511,433024223,452930459,472882027,492876847,512927357,533000389,553105243,573259391,593441843,613651349,633910099,654188383,674506081,694847533,715225739,735632791,756065159,776531401,797003413,817504243,838041641,858599503,879190747,899809343,920419813,941083981,961748927,982451653,1003162753,1023893771,1044645379,1065433423,1086218491,1107029837,1127870669,1148739811,1169604791,1190494759,1211405357,1232332807,1253270831,1274224957,1295202449,1316196199,1337195521,1358208601,1379256017,1400305337,1421376527,1442469307,1463554999,1484670157,1505776939,1526922013,1548074321,1569250357,1590425971,1611623773,1632828047,1654054489,1675293211,1696528903,1717783147,1739062363,1760341421,1781636611,1802933611,1824261409,1845587707,1866941107,1888303061,1909662901,1931045213,1952429173,1973828641,1995230813,2016634091,2038074743,2059519669,2080975129,2102429869,2123895971,2145390523,2166877459,2188381931,2209898659,2231422087,2252945251,2274464657,2296014671,2317573351,2339150657,2360739643,2382327887,2403927803,2425530169,2447142727,2468776129,2490401359,2512046833,2533680361,2555333789,2576983867,2598653287,2620343177,2642042561,2663748103,2685457421,2707161461,2728895893,2750638547,2772373133,2794119103,2815869317,2837630963,2859399863,2881172057,2902958801,2924759963,2946551921,2968362013,2990179831,3012017609,3033850613,3055685081,3077513171,3099373523,3121238909,3143102429,3164969219,3186853091,3208726513,3230631829,3252531827,3274449029,3296363293,3318283333,3340200037,3362143849,3384088471,3406031009,3427973503,3449931889,3471893387,3493866473,3515827213,3537803429,3559788179,3581791331,3603805021,3625809167,3647809349,3669829403,3691857803,3713895587,3735911761,3757961567,3780008329,3802067851,3824122121,3846198203,3868277299,3890351567,3912435773,3934544879,3956628523,3978735073,4000846301,4022963641,4045093753,4067203991,4089353447,4111485199,4133602927,4155754901,4177926497,4200086549,4222234741,4244406151,4266581161,4288745689,4310939683,4333114999,4355300617,4377488131,4399700561,4421905661,4444120783,4466344853,4488579211,4510797959,4533027899,4555267027,4577497597,4599747011,4622005693,4644257873,4666527007,4688780647,4711054291,4733322353,4755585781,4777890881,4800184007,4822476077,4844782819,4867094867,4889388631,4911707267,4934029189,4956340187,4978668371,5001022591,5023334359,5045684663,5068037123,5090380741,5112733757,5135092331,5157448663,5179816661,5202181597,5224558357,5246938799,5269312091,5291699641,5314096859,5336500537,5358893273,5381299531,5403718189,5426132731,5448551179,5470966379,5493393271,5515825573,5538271547,5560695863,5583129547,5605571519,5628008233,5650458269,5672909131,5695356911,5717829097,5740295849,5762767343,5785258351,5807739811,5830233817,5852719141,5875200029,5897707297,5920216007,5942714627,5965232983,5987713507,6010236857,6032763691,6055304117,6077818823,6100342289,6122882657,6145389581,6167937907,6190481743,6213011977,6235575917,6258136327,6280689743,6303247901,6325810637,6348396851,6370967773,6393551467,6416141357,6438741431,6461335109,6483922183,6506515801,6529093873,6551697491,6574300543,6596900039,6619508989,6642115709,6664751449,6687351857,6709980523,6732611737,6755252149,6777880423,6800517007,6823160789,6845814071,6868476247,6891136907,6913774603,6936443473,6959111611,6981773209,7004443339,7027107881,7049773657,7072445857,7095125617,7117819117,7140493427,7163197267,7185899801,7208605991,7231306219,7254012631,7276711993,7299437377,7322146999,7344842627,7367575799,7390308791,7413014827,7435737887,7458467857,7481210459,7503945209,7526681699,7549438951,7572173381,7594955549,7617720437,7640463109,7663231087,7685997841,7708770767,7731532979,7754306137,7777064947,7799850211,7822624247,7845389029,7868170889,7890974177,7913744827,7936555091,7959343939,7982133091,8004928709,8027723749,8050542697,8073344459,8096153687,8118971701,8141800657,8164628191,8187459113,8210262293,8233090597,8255916589,8278737359,8301579067,8324425997,8347269191,8370100303,8392965599,8415813401,8438659127,8461538531,8484400081,8507262073,8530123933,8552980351,8575846297,8598720577,8621600237,8644481159,8667382733,8690273759,8713149233,8736028057,8758937903,8781842093,8804729699,8827631101,8850522587,8873432053,8896343893,8919267671,8942177977,8965095091,8988013367,9010926083,9033844601,9056769439,9079702733,9102626041,9125563549,9148509569,9171464807,9194418049,9217347743,9240279799,9263218351,9286157297,9309109471,9332048851,9355029863,9378002057,9400949587,9423913223,9446878729,9469852559,9492835949,9515814827,9538781773,9561775841,9584743309,9607732703,9630702359,9653704481,9676680427,9699658559,9722645497,9745640363,9768651857,9791657767,9814655027,9837667481,9860683127,9883692017,9906708083,9929727163,9952744433,9975772717,9998789179,10021801547,10044846743,10067892493,10090917877,10113958157,10137004357,10160045309,10183081933,10206146227,10229186897,10252242353,10275306781,10298341021,10321387183,10344464261,10367519563,10390585559,10413670321,10436728957,10459805417,10482884821,10505964869,10529046763,10552148077,10575209467,10598277169,10621372481,10644447329,10667551211,10690631467,10713727043,10736835247,10759918297,10783008619,10806085439,10829190481,10852325903,10875445517,10898545213,10921655989,10944770911,10967906377,10991026589,11014146751,11037271757,11060397583,11083528283,11106647143,11129774333,11152893919,11176036693,11199165031,11222335207,11245478549,11268626009,11291781331,11314940113,11338081481,11361255487,11384399891,11407568779,11430737359,11453897617,11477051947,11500205947,11523371179,11546521937,11569682393,11592839717,11616020609,11639203421,11662367891,11685541321,11708706263,11731910789,11755091441,11778293507,11801484067,11824679047,11847876533,11871076571,11894259677,11917463821,11940682979,11963902331,11987104663,12010317559,12033527819,12056733197,12079947667,12103145213,12126375277,12149578817,12172797893,12196034771,12219260033,12242474513,12265703959,12288938813,12312169801,12335417357,12358651969,12381892093,12405136253,12428375423,12451606073,12474836203,12498081263,12521337767,12544578539,12567822851,12591098053,12614364839,12637628257,12660897863,12684167081,12707432041,12730703669,12753968221,12777222833,12800506879,12823773713,12847049867,12870320797,12893587657,12916867853,12940140859,12963422833,12986713643,13010011507,13033291087,13056596387,13079887349,13103192441,13126492867,13149797443,13173092003,13196382817,13219684637,13242989777,13266303629,13289618149,13312928729,13336237711,13359555403,13382874787,13406172119,13429500449,13452816827,13476146219,13499471273,13522810879,13546140761,13569481153,13592796691,13616128499,13639453571,13662784283,13686140227,13709489839,13732809179,13756159661,13779489821,13802833129,13826206699,13849557133,13872921869,13896282017,13919632949,13942985677,13966339301,13989703151,14013085423,14036449027,14059819243,14083200017,14106590447,14129947421,14153316469,14176686661,14200063853,14223438769,14246824121,14270199259,14293566641,14316943831,14340327601,14363733169,14387109739,14410507717,14433895277,14457290273,14480672251,14504076287,14527476781,14550882943,14574274903,14597673287,14621080433,14644477607,14667894713,14691301187,14714715583,14738128133,14761538761,14784944609,14808361033,14831771683,14855191427,14878625551,14902063247,14925482141,14948903159,14972319589,14995769359,15019199407,15042641231,15066064399,15089507431,15112928683,15136366507,15159782801,15183225461,15206675501,15230122499,15253581503,15277030949,15300478981,15323944747,15347401327,15370860707,15394296349,15417763909,15441229417,15464682059,15488152063,15511615213,15535073131,15558537179,15581984489,15605465147,15628934753,15652395767,15675869369,15699342107,15722819069,15746312837,15769789859,15793278041,15816764617,15840236969,15863734879,15887221307,15910721909,15934218877,15957711919,15981194077,16004704907,16028208949,16051692389,16075200437,16098700349,16122185251,16145713757,16169207209,16192706723,16216230847,16239732961,16263252469,16286768243,16310277421,16333797133,16357317667,16380845321,16404379931,16427896939,16451405147,16474937263,16498458203,16522007387,16545527473,16569049423,16592580271,16616117249,16639648327,16663176457,16686714617,16710243757,16733789791,16757324299,16780857791,16804395323,16827948331,16851492389,16875026921,16898582551,16922128913,16945676833,16969232831,16992788123,17016352853,17039908037,17063455231,17087040307,17110593779,17134183849,17157748189,17181304009,17204844991,17228437399,17252006663,17275580207,17299158791,17322727889,17346308407,17369892361,17393478391,17417067617,17440649059,17464243799,17487818207,17511402317,17534985101,17558571353,17582163853,17605745957,17629346131,17652951847,17676555929,17700132167,17723722337,17747328779,17770941337,17794544659,17818153021,17841755807,17865351199,17888948849,17912561749,17936162863,17959775629,17983392851,18007002833,18030631279,18054236957,18077835707,18101473441,18125114831,18148749503,18172358299,18195990523,18219611903,18243245249,18266868043,18290495647,18314146363,18337768541,18361403107,18385019473,18408668081,18432312097,18455939659,18479565331,18503215349,18526876243,18550524281,18574160147,18597802121,18621465143,18645104897,18668758501,18692401547,18716053529,18739706641,18763374163,18787026541,18810698639,18834375961,18858014761,18881690141,18905355607,18929017769,18952657291,18976321181,18999999247,19023678341,19047324319,19071004067,19094676619,19118342011,19142007793,19165668289,19189345667,19213023737,19236701629,19260369091,19284030163,19307730779,19331404121,19355106737,19378790443,19402471901,19426161311,19449853327,19473535801,19497229937,19520931557,19544647501,19568338991,19592058341,19615753721,19639441429,19663134061,19686827359,19710531427,19734231103,19757957959,19781669923,19805390141,19829092147,19852798853,19876517251,19900244753,19923940733,19947663787,19971369137,19995094501,20018829139,20042546479,20066267449,20089983467,20113707833,20137450349,20161165741,20184892661,20208604813,20232330607,20256063827,20279812313,20303537887,20327281421,20351017417,20374752851,20398468697,20422213579,20445956029,20469698573,20493442457,20517175201,20540918737,20564655967,20588418127,20612162513,20635906957,20659667323,20683416889,20707162057,20730928457,20754680437,20778452413,20802207407,20825943899,20849700449,20873461241,20897216723,20920981057,20944748239,20968502717,20992276849,21016060633,21039803297,21063577111,21087345673,21111112453,21134879981,21158660447,21182429231,21206221633,21229997209,21253770247,21277541851,21301334869,21325121471,21348901591,21372698029,21396488129,21420285281,21444070979,21467857421,21491636993,21515425007,21539231993,21563007139,21586802491,21610588367,21634369819,21658177231,21681955847,21705755437,21729529027,21753360833,21777170579,21801001571,21824814679,21848603809,21872402441,21896224949,21920047451,21943865213,21967658491,21991473979,22015282979,22039085767,22062906941,22086742277,22110536761,22134365933,22158185429,22182001447,22205818561,22229659609,22253484221,22277307439,22301154229,22325014259,22348834747,22372678957,22396485743,22420309489,22444149523,22467982217,22491808597,22515644681,22539470101,22563323957,22587158327,22610980499,22634818039,22658652391,22682508703,22706363567,22730202623,22754048797,22777909421,22801763489};
const int maxn = 151010, divs = 1000000;
int n, tot, prime[maxn];
bool vis[maxn];
bool check(const LL &x)
{
	if(x < maxn)
		return !vis[x];
	for(int i = 0; i < tot && prime[i] <= x / prime[i]; ++i)
		if(x % prime[i] == 0)
			return 0;
	return 1;
}
int main()
{
	vis[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0; j < tot && (LL)i * prime[j] < maxn; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	scanf("%d", &n);
	int cnt = n / divs * divs;
	long long now = ans[n / divs];
	if(cnt != n && n - cnt > divs - (n - cnt))
	{
		now = ans[n / divs + 1];
		cnt += divs;
	}
	while(cnt < n)
		if(check(++now))
			++cnt;
	while(cnt > n)
		if(check(--now))
			--cnt;
	printf("%lld\n", now);
	return 0;
}