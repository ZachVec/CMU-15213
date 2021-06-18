#ifndef CSIM_H
#define CSIM_H
#define uint64 unsigned long long
const char *ht = "hit";
const char *ms = "miss";
const char *me = "miss eviction";
int missCnt = 0, hitCnt = 0, evictCnt = 0;

struct CacheLine{
	uint64  vbit, tag, ref;
};

typedef struct CacheLine *pSet;
typedef pSet *pCache;
pCache cache;
size_t sBits, setNum, bBits, E;
int verbose;

// cache related functions
int initCache();
int freeCache();
int isCached(uint64 setIndex, uint64 tag, int ref);
int isEvicted(uint64 setIndex, uint64 tag, int ref);
void simulate(FILE *fp);

// auxiliary functions
int readOption(int argc, char *argv[], FILE **fpp);
void printHelp();
#endif

