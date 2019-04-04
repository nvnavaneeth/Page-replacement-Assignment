#ifndef __BASE_PAGE_REPLACER__
#define __BASE_PAGE_REPLACER__

// Implements the base class for all the page replacement algorithms used
// in this project.

#include<memory>

// Struct defining the result of a read_page operation.
struct ReadPageResult {
  // bool value that is set to true when a page fault occurs while trying to
  // read a page.
  bool page_fault;
  // Page no. of the page removed from memory to load the required page. If 
  // no page was removed, then set to -1. (Valid only if page_fault it set to
  // true.
  int replaced_page_no;
};

class BasePageReplacer {

  public:
    // The core function, to be implemented by all derived classes.
    virtual std::shared_ptr<ReadPageResult> read_page(int page_no) = 0;
} ;

#endif  // __BASE_PAGE_REPLACER__
