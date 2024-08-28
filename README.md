# Cache Simulator !

The aim of this project was to design and implement a cache simulator capable of analyzing and comparing various cache configurations. The simulator reads memory access traces from standard input, simulates cache behavior based on specified parameters, and outputs summary statistics.

## Design Parameters

The cache simulator is configured with the following design parameters:

    Number of sets in the cache (a positive power-of-2)
    Number of blocks in each set (a positive power-of-2)
    Number of bytes in each block (a positive power-of-2, at least 4)
    Write-allocate or no-write-allocate
    Write-through or write-back
    Eviction policy: LRU (least-recently-used) or FIFO (first-in, first-out)



## Cache Configurations

Different combinations of the design parameters result in different cache configurations:

    Direct-mapped cache: 1 set with 1 block per set
    Set-associative cache: n sets with m blocks per set
    Fully associative cache: 1 set with n blocks


## Build

In your desired directory, run the following command to compile cache.cpp :
```c++
make
```
You may also run "make clean" to avoid any possible errors and then run "make" in the correct directory or folder.
```c++
make clean
make
```
## Usage
For running the executable:
```c++
./cacheSim 256 4 16 write-allocate write-back fifo < example_trace_file
```
```c++
./cacheSim 256 4 16 no-write-allocate write-back lru < example_trace_file
```
You may change the Design Parameters according to your needs.

## Persormance

### Assumptions
- memory-stall clock cycles come primarily from cache misses
- in systems with a reasonable
write buffer depth (e.g., four or more words) and a memory capable
of accepting writes at a rate that significantly exceeds the average
write frequency in programs (e.g., by a factor of 2), the write buffer
stalls will be small, and we can safely ignore them.

### Write-Allocate/No-Write-Allocate vs Write-Back/Write-Through vs fifo/lru
for [ ./cacheSim 256 4 16 _ _ _ < trace_file]

WA | WB | fifo:

    total_loads - 318197
    total_store - 197486
    load_hits - 314171
    load_miss - 4026
    store_hits - 188047
    store_misses - 9439
    total_cycles - 9845283
    hit rate - 97.38%
    miss rate - 2.61%

WA | WB | lru:

    total_loads - 318197
    total_store - 197486
    load_hits - 314798
    load_miss - 3399
    store_hits - 188250
    store_misses - 9236
    total_cycles - 9344483
    hit rate - 97.55%
    miss rate - 2.45%

WA | WT | fifo:

    total_loads - 318197
    total_store - 197486
    load_hits - 314171
    load_miss - 4026
    store_hits - 188047
    store_misses - 9439
    total_cycles - 25650283
    hit rate - 97.38%
    miss rate - 2.61%

WA | WT | lru:

    total_loads - 318197
    total_store - 197486
    load_hits - 314798
    load_miss - 3399
    store_hits - 188250
    store_misses - 9236
    total_cycles - 25318283
    hit rate - 97.54%
    miss rate - 2.45%

NWA | WB | fifo:

    total_loads - 318197
    total_store - 197486
    load_hits - 311017
    load_miss - 7180
    store_hits - 163705
    store_misses - 33781
    total_cycles - 8033202
    hit rate - 92.05%
    miss rate - 7.94%

NWA | WB | lru:

    total_loads - 318197
    total_store - 197486
    load_hits - 311613
    load_miss - 6584
    store_hits - 164819
    store_misses - 32667
    total_cycles - 7565716
    hit rate - 92.38%
    miss rate - 7.61%

NWA | WT | fifo:

    total_loads - 318197
    total_store - 197486
    load_hits - 311017
    load_miss - 7180
    store_hits - 163705
    store_misses - 33781
    total_cycles - 23102502
    hit rate - 92.05%
    miss rate - 7.94%


NWA | WT | lru:

    total_loads - 318197
    total_store - 197486
    load_hits - 311613
    load_miss - 6584
    store_hits - 164819
    store_misses - 32667
    total_cycles - 22865216
    hit rate - 92.38%
    miss rate - 7.61%
 

## Graph Analysis

### Figure_1
By the above data, we can observe that the Least Number of Cycles is of "NO-Write-Allocate | Write-Back | lru" while the worst performing is "Write-Allocate | Write-Through | fifo". 
Therefore, if we are low on resources we might be inclined towards the former configuration i.e. "No-Write-Allocate | Write-Back | lru".

### Figure_2
WA results in more load Hits of different configurations compared to NWA with an approximate difference between best and worst being ~3000.

### Figure_3
We can see that WA results in less number of Load_misses compared to NWA, with a difference of ~3000.

### Figure_4
WA results in greater number of store_hits compared to NWA, with a difference of ~2500. Among WA, (WB, lru) performs the best.

### Figure_5
NWA results in greater number of store_misses compared to WA with an approximate difference of 22500. Among WA, again (WB, lru) performs the best. 

We can select the best configurations by drawing analyzing the above conclusions of figures.

## Set_size, number of Block and Block_size Analysis.
for [ ./cacheSim _ _ _ write-allocate write-back lru < trace_file]

### Figure_6
We can observe that number of cycles decreases as set size increases. 

16 4 16:

    total_loads - 318197
    total_store - 197486
    load_hits - 297243
    load_miss - 20954
    store_hits - 184121
    store_misses - 13365
    total_cycles - 21360883

32 4 16:

    total_loads - 318197
    total_store - 197486
    load_hits - 307659
    load_miss - 10538
    store_hits - 186542
    store_misses - 10944
    total_cycles - 14370483


64 4 16:

    total_loads - 318197
    total_store - 197486
    load_hits - 312099
    load_miss - 6098
    store_hits - 187526
    store_misses - 9960
    total_cycles - 11414883


128 4 16:

    total_loads - 318197
    total_store - 197486
    load_hits - 314007
    load_miss - 4190
    store_hits - 188015
    store_misses - 9471
    total_cycles - 10071683

256 4 16:
    total_loads - 318197
    total_store - 197486
    load_hits - 314798
    load_miss - 3399
    store_hits - 188250
    store_misses - 9236
    total_cycles - 9344483

512 4 16:

    total_loads - 318197
    total_store - 197486
    load_hits - 315211
    load_miss - 2986
    store_hits - 188468
    store_misses - 9018
    total_cycles - 8607683

## Graph Analysis for 6

### Figure_7
We can observe that number of cycles increases as set size of block increase. But we can also observe that Misses decreasing as block size increases.


64 4 16:

    total_loads - 318197
    total_store - 197486
    load_hits - 312099
    load_miss - 6098
    store_hits - 187526
    store_misses - 9960
    total_cycles - 11414883


64 4 32:

    total_loads - 318197
    total_store - 197486
    load_hits - 314756
    load_miss - 3441
    store_hits - 192423
    store_misses - 5063
    total_cycles - 11994883

64 4 64:

    total_loads - 318197
    total_store - 197486
    load_hits - 316157
    load_miss - 2040
    store_hits - 194821
    store_misses - 2665
    total_cycles - 13050083


64 4 128:

    total_loads - 318197
    total_store - 197486
    load_hits - 317016
    load_miss - 1181
    store_hits - 196045
    store_misses - 1441
    total_cycles - 14150883


64 4 256:

    total_loads - 318197
    total_store - 197486
    load_hits - 317480
    load_miss - 717
    store_hits - 196697
    store_misses - 789
    total_cycles - 15581283


64 4 512:

    total_loads - 318197
    total_store - 197486
    load_hits - 317731
    load_miss - 466
    store_hits - 197050
    store_misses - 436
    total_cycles - 17360483

## Best Cache

For
In my opinion the best caches are among Write-Allocate | Write-Back | lru. And within them we can choose according to the available resources which fits our needs best.



