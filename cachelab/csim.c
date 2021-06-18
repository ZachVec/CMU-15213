#include <stdio.h>
#include <malloc.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include "cachelab.h"
#include "csim.h"

int main(int argc, char *argv[]) {
    FILE *fp = NULL;
    if(!readOption(argc, argv, &fp)) return 0;
    if(!initCache()) return 0;
    simulate(fp);
    fclose(fp);
    printSummary(hitCnt, missCnt, evictCnt);
    freeCache();
    return 0;
}

int initCache() {
    cache = (pCache) calloc(setNum, sizeof(pSet));
    for(size_t i = 0; i < setNum; i++) {
        cache[i] = (pSet) calloc(E, sizeof(struct CacheLine));
    }
    return 1;
}

int freeCache() {
    for(size_t i = 0; i < setNum; i++) {
        free(cache[i]);
    }
    free(cache);
    return 1;
}

int isCached(uint64 setIndex, uint64 tag, int ref) {
    /*
     * param: 
     *     - setIndex: where to look up for the block with tag
     *  - tag: block identifier
     *  - ref: reference timestamp, 
     *         if block is cached, update reference timestamp
     *         if not cached, do nothing
     * return value:
     *         if cached, return 1;
     *         if not cached, return 0;
     */
    pSet set = cache[setIndex];
    for(size_t i = 0; i < E; i++) {
        if(set[i].tag == tag && set[i].vbit) {
            // update reference timestamp
            set[i].ref = ref;
            return 1;
        }
    }
    return 0;
}

int isEvicted(uint64 setIndex, uint64 tag, int ref) {
    /*
     * param:
     *         setIndex: where to seek for evictim
     *         tag: put the block with this tag into set[setIndex]
     *         ref: reference timestamp
     * return value:
     *         if a block is evicted, return 1;
     *         if no block is evicted, return 0;
     */
    pSet set = cache[setIndex];
    int minRef = ref, minIdx = -1;
    for(size_t i = 0; i < E; i++) {
        if(set[i].ref >= minRef) continue;
        minRef = set[i].ref;
        minIdx = i;
    }
    if(minIdx == -1) return 0;
    set[minIdx].tag = tag;
    set[minIdx].ref = ref;
    if(set[minIdx].vbit) return 1;
    else {
        set[minIdx].vbit = 1;
        return 0;
    }
}

void simulate(FILE *fp) {
    char op;
    int cf, ef;
    uint64 addr, idx, tag;
    for(int ref = 1, byte; fscanf(fp, " %c %llx,%d", &op, &addr, &byte) != EOF; ++ref) {
        idx = (addr >> bBits) % setNum;
        tag = (addr >> (bBits + sBits));
        if(op == 'L' || op == 'S') {
            cf = isCached(idx, tag, ref);
            if(cf) ++hitCnt;
            else {
                ++missCnt;
                evictCnt += (ef = isEvicted(idx, tag, ref));
            }
            if(verbose) printf("%c %llx,%d %s\n", op, addr, byte, cf ? ht : (ef ? me : ms));
        }
        else if(op == 'M') {
            cf = isCached(idx, tag, ref);
            if(cf) hitCnt += 2;
            else {
                ++hitCnt;
                ++missCnt;
                evictCnt += (ef = isEvicted(idx, tag, ref));
            }
            if(verbose) {
                if(cf) printf("%c %llx,%d %s %s\n", op, addr, byte, ht, ht);
                else printf("%c %llx,%d %s %s\n", op, addr, byte, ef ? me : ms, ht);
            }
        }
        else continue;
    }
}

int readOption(int argc, char *argv[], FILE **fpp) {
    /*
     * There are a few options:
     * -h: Optional help flag that prints usage info
     * -v: Optional verbose flag that displays trace info
     * -s <s>: Number of set index bits
     * -E <E>: Number of Associativity
     * -b <b>: Number of block bits
     * -t <tracefile>: Name of the tracefile
     */
    int opt;
    verbose = 0;
    while((opt = getopt(argc, argv, "-hvs:E:b:t:")) != -1) {
        switch(opt) {
        case 's': 
            sBits = atoi(optarg);
            setNum = 1 << sBits;
            break;
        case 'E':
            E = atoi(optarg); break;
        case 'b':
            bBits = atoi(optarg); 
            break;
        case 'v':
            verbose = 1; break;
        case 't':
            *fpp = fopen(optarg, "r"); break;
        default:
            printHelp(); return 0;
        }
    }
    return 1;
}

void printHelp(){
    printf("Usage: ./csim-ref [-hv] -s <num> -E <num> -b <num> -t <file>\n"
            "Options:\n"
            "  -h         Print this help message.\n"
            "  -v         Optional verbose flag.\n"
            "  -s <num>   Number of set index bits.\n"
            "  -E <num>   Number of lines per set.\n"
            "  -b <num>   Number of block offset bits.\n"
            "  -t <file>  Trace file.\n\n"
            "Examples:\n"
            "  linux>  ./csim-ref -s 4 -E 1 -b 4 -t traces/yi.trace\n"
            "  linux>  ./csim-ref -v -s 8 -E 2 -b 4 -t traces/yi.trace\n");
}

