#include<iostream>
#include<fstream>
#include<vector>
#include<stdlib.h>
#include<ctime>
#include<memory>
#include"page_replacement_algos.h"

using namespace std;

// Length of the page read sequences.
const int kSequenceLength = 50;
// The number of sequnces that will be used for determining the average page
// fault rate for a (num_pages, num_frames) combination.
const int kNumSequencesPerStep = 100;
// The different values of num_frames  parameter that will be used.
const int kValuesNumFrames[] = {1, 2, 3, 4, 5, 6};
// The different values of num_pages parameter that will be used.
const int kValuesNumPages[] = {6, 8, 10, 12};


void run_one_step(const int num_pages, const int num_frames,
    float fault_count[]) {
  // Initialize page fault counts.
  int total_faults_counter = 0, total_faults_stack = 0, total_faults_aging= 0, 
      total_faults_clock = 0;

  for (int seq_no = 1; seq_no <= kNumSequencesPerStep; ++seq_no) {
    // Generate sequence.
    vector<int> sequence(kSequenceLength);
    for (int i = 0; i < kSequenceLength; ++i) {
      sequence[i] = rand()%num_pages + 1;
    }
    int fault_count, avg_read_time;
    ReadSequenceLRUClock(sequence, num_frames, fault_count, avg_read_time);
    total_faults_clock += fault_count;
  }

  fault_count[0] = total_faults_counter / float(kNumSequencesPerStep);
  fault_count[1] = total_faults_stack / float(kNumSequencesPerStep);
  fault_count[2] = total_faults_aging / float(kNumSequencesPerStep);
  fault_count[3] = total_faults_clock / float(kNumSequencesPerStep);
}


void run_tester() {
  ofstream result_file("result.csv");
  // Save the header.
  result_file<<"num_page, num_frames, lru_counter, lru_stack, lru_aging,"
             <<" lru_clock \n";

  const int num_page_values = 
      sizeof(kValuesNumPages)/sizeof(kValuesNumPages[0]);
  const int num_frame_values = 
      sizeof(kValuesNumFrames)/sizeof(kValuesNumFrames[0]);

  for (int i = 0; i < num_page_values; ++i ) {
    for (int j = 0; j < num_frame_values; ++j) {
      int num_pages = kValuesNumPages[i];
      int num_frames = kValuesNumFrames[j];

      float fault_count[4];

      run_one_step(num_pages, num_frames, fault_count);

      // Save results.
      result_file<<num_pages<<','<<num_frames<<','<<fault_count[0]<<','
                 <<fault_count[1]<<','<<fault_count[2]<<','
                 <<fault_count[3]<<endl;
      cout<<"Fault count for num_pages = "<<kValuesNumPages[i]
          <<" and num_frames = "<<kValuesNumFrames[j]<< " is : "<<fault_count[3]
          <<endl;
    }
  }
}


int main() {
  srand(time(0));

  // vector<int> sequence({0, 4, 1, 4, 2, 4, 3, 4, 2, 4, 0, 4, 1, 4, 2, 4, 3, 4});
  // unique_ptr<BasePageManager> page_manager = make_unique<PageManagerLRUClock>(5);

  run_tester();
  return 0;
}
