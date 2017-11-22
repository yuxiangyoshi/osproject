#ifndef PROGRESS_H_
#define PROGRESS_H_

#include <mutex>

namespace coen {

class Progress {
 public:
  Progress(int num_tasks) : total_(num_tasks),
                            tenth_(num_tasks / 10),
                            dispatched_(0),
                            done_(0) {}

  bool FetchTask() {
    std::lock_guard<std::mutex> lock(mtx_);

    if (dispatched_ >= total_) {
      return false;
    }

    ++dispatched_;
    return true;
  }

  void ReportTaskDone() {
    std::lock_guard<std::mutex> lock(mtx_);

    ++done_;
    assert(done_ <= total_);
    if (tenth_ > 0 && done_ % tenth_ == 0) {
      std::printf("...[%6d / %d]\n", done_, total_);
    }
  }

 private:
  std::mutex mtx_;  // guard the whole class

  int total_;
  int tenth_;
  int dispatched_;
  int done_;
};


}  // namespace coen

#endif  // PROGRESS_H_
