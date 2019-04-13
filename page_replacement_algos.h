#ifndef __PAGE_REPLACEMENT_ALGOS__
#define __PAGE_REPLACEMENT_ALGOS__

// A bare minimum implementation of common page replacement algorithms just to test their page fault rate.

#include<vector>

// Implements approximate LRU clock (second chance) algorithm.
void ReadSequenceLRUClock(const std::vector<int>& sequence,
    const int num_frames, int& fault_count, int& avg_read_time);


#endif  // __PAGE_REPLACEMENT_ALGOS__
