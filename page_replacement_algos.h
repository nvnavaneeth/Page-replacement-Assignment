#ifndef __PAGE_REPLACEMENT_ALGOS__
#define __PAGE_REPLACEMENT_ALGOS__


#include<memory>

// Struct defining the result of a ReadPage operation.
struct ReadPageResult {
  // bool value that is set to true when a page fault occurs while trying to
  // read a page.
  bool page_fault;
  // Page no. of the page removed from memory to load the required page. If 
  // no page was removed, then set to -1. (Valid only if page_fault it set to
  // true.
  int replaced_page_no;
};

// An abstract base class for all the page replacement algorithms used
// in this project.
class BasePageManager{

  public:
    // The core function, to be implemented by all derived classes.
    virtual std::shared_ptr<ReadPageResult> ReadPage(int page_no) = 0;
};

// Class that implements the LRU algorithm using counters.
class PageManagerLRUCounter : public BasePageManager {

  public:
    std::shared_ptr<ReadPageResult> ReadPage(int page_no);
};

// Class that implements the LRU algorithm using stack.
class PageManagerLRUStack : public BasePageManager {

  public:
    std::shared_ptr<ReadPageResult> ReadPage(int page_no);
};

// Class that implements the LRU algorithm using aging registers.
class PageManagerLRUAging : public BasePageManager {

  public:
    std::shared_ptr<ReadPageResult> ReadPage(int page_no);
};

// Class that implements the approximate LRU clock algorithm.
class PageManagerLRUClock : public BasePageManager {

  public:
    std::shared_ptr<ReadPageResult> ReadPage(int page_no);
};

#endif  // __PAGE_REPLACEMENT_ALGOS__
