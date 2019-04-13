#include"page_replacement_algos.h"

#include<iostream>

using namespace std;

void ReadSequenceLRUCounter(const vector<int>& sequence, const int num_frames,
    int& fault_count, int& avg_read_time) {
  // List of pages in memory.
  int* page_list = new int[num_frames];
  // Reference count of corresponding page in page_list.
  int* ref_count = new int[num_frames];

  delete[] page_list;
  delete[] ref_count;
}


//---------------------------- LRU Clock --------------------------------------
void ReadSequenceLRUClock(const vector<int>& sequence, const int num_frames,
    int& fault_count, int& avg_read_time) {
  // List of pages in memory.
  int* page_list = new int[num_frames];
  // Bool array that stores the second chance status of the corresponding page
  // in page_list.
  bool* has_second_chance = new bool[num_frames];
  // Current size of page_list.
  int cur_list_size = 0;
  // The index in page_list at which the clock_pointer is pointing.
  int clock_pointer = 0;

  fault_count = 0;
  for (int page_num : sequence) {
    // Search for the page in page_list.
    bool found = false;
    for (int i = 0; i < cur_list_size; ++i) {
      if (page_list[i] == page_num) {
        // Update has_second_chance status.
        has_second_chance[i] = true;
        found = true;
        break;
      }
    }

    if (found)
      continue;
    // Page fault.
    fault_count++;

    // If free frames are available, add to one.
    if (cur_list_size < num_frames) {
      page_list[cur_list_size] = page_num;
      has_second_chance[cur_list_size] = false;

      cur_list_size++;
      continue;
    }

    // Replace a page.
    while(true) {
      if (!has_second_chance[clock_pointer]) {
        // Replace this page. has_second_chance remains false.
        page_list[clock_pointer] = page_num;

        clock_pointer = (clock_pointer + 1) % num_frames;
        break;
      }

      has_second_chance[clock_pointer] = false;
      clock_pointer = (clock_pointer + 1) % num_frames;
    }
  }

  delete[] page_list;
  delete[] has_second_chance;
}
//----------------------------------------------------------------------------
