#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// Rutgers University 2021 Spring CS 211 Computer Architecture
// Assignment based on CS:APP Cache Lab

// 64-bit memory address
typedef unsigned long long int mem_addr_t;

// cache properties
unsigned char s = 0; // set index bits
unsigned short S = 1<<0; // set count

unsigned char E = 16; // way associative cache; lines per set

unsigned char b = 4; // block offset bits
// unsigned short B = 1<<4; // block size in bytes

// fully associative cache line
typedef struct cache_line {
    mem_addr_t tag;
    struct cache_line* next_cache_line;
} cache_line_t;

typedef struct fifo_cache_set {
    cache_line_t* front; // front (head) of the queue
    cache_line_t* back; // back (tail) of the queue
    unsigned char occupancy;
} fully_associative_fifo_cache_t;

// accessData - Access data at memory address addr.
void accessData (
    mem_addr_t addr,
    fully_associative_fifo_cache_t* cache,
    unsigned int* hit_count, // If it is already in cache, increase hit_count
    unsigned int* miss_count, // If it is not in cache, bring it in cache, increase miss_count
    unsigned int* eviction_count // Also increase eviction_count if a line is evicted
) {

    // Cache indices for this address
    mem_addr_t tag = addr >> (s+b);

    // Cache hit
    cache_line_t* curr_line = cache->front;
    while ( curr_line != NULL ) {
        if ( curr_line->tag == tag ) {
            (*hit_count)++;
            return;
        }
        curr_line = curr_line->next_cache_line;
    }

    // Otherwise, record a cache miss
    (*miss_count)++;

    // If cache is full, evict oldest line due to FIFO cache replacement policy
    if ( cache->occupancy == E ) {
        // dequeue from front of FIFO, update occupancy, and record an eviction
        cache_line_t* new_front = cache->front->next_cache_line;
        free(cache->front);
        cache->front = new_front;

        cache->occupancy--;

        (*eviction_count)++;
    }

    // Due to cache miss, enqueue cache line, and update occupancy
    cache_line_t* new_line = calloc(1, sizeof(cache_line_t));
    new_line->tag = tag;

    if (cache->occupancy == 0) {
        cache->front = new_line;
        cache->back = new_line;
    } else {
        cache->back->next_cache_line = new_line;
        cache->back = cache->back->next_cache_line;
    }

    cache->occupancy++;
}

int main(int argc, char* argv[]) {

    // path to memory trace
    if ( argc!= 2 ) {
        printf( "Usage: ./fullyAssociative <mem_trace_file>\n" );
        exit( EXIT_FAILURE );
    }
    char* mem_trace_file = argv[1];
    // char* mem_trace_file = "/home/velcro/Documents/Undergrad/CS/CompArch-211/2022_0s_221/pa5/fullyAssociative/tests/trace_0.txt";
    FILE *fp = fopen(mem_trace_file, "r");
    if (!fp) {
        fprintf(stderr, "Error opening file '%s'\n", mem_trace_file);
        exit( EXIT_FAILURE );
    }

    fully_associative_fifo_cache_t cache = { .front=NULL, .back=NULL, .occupancy=0 };
    // cache simulation statistics
    unsigned int miss_count = 0;
    unsigned int hit_count = 0;
    unsigned int eviction_count = 0;

    // Loop through until we are done with the file.
    size_t line_buf_size = 256;
    char line_buf[line_buf_size];

    while ( fgets(line_buf, line_buf_size, fp) != NULL ) {

        // replay the given trace file against the cache
        if ( line_buf[1]=='L' || line_buf[1]=='S' || line_buf[1]=='M' ) {
            char access_type = '\0';
            mem_addr_t addr = 0;
            unsigned int len = 0;
            sscanf ( line_buf, " %c %llx,%u", &access_type, &addr, &len );

            if ( access_type=='L' || access_type=='S' || access_type=='M') {
                accessData(addr, &cache, &hit_count, &miss_count, &eviction_count);
            }

            // If the instruction is M indicating L followed by S then access again
            if(access_type=='M')
                accessData(addr, &cache, &hit_count, &miss_count, &eviction_count);
        }
    }

    cache_line_t* curr_line = cache.front;
    while ( curr_line != NULL ) {
        cache_line_t* temp = curr_line;
        curr_line = curr_line->next_cache_line;
        free(temp);
    }
    fclose(fp);

    /* Output the hit and miss statistics for the autograder */
    printf("hits:%d misses:%d evictions:%d\n", hit_count, miss_count, eviction_count);

    exit( EXIT_SUCCESS );
}
