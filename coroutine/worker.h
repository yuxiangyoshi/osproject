#ifndef WORKER_H_
#define WORKER_H_

#include <memory>
#include <string>

#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/streambuf.hpp>

#include "progress.h"

namespace coen {

class Worker {
 public:
  Worker(std::shared_ptr<boost::asio::io_service> io_service,
         std::string request,
         std::shared_ptr<Progress> progress);

  void Run(boost::asio::yield_context yield);

 private:
  void DoTask(boost::asio::yield_context yield);

  std::shared_ptr<boost::asio::io_service> io_service_;
  std::string request_;
  std::shared_ptr<Progress> progress_;
};

}  // namespace coen

#endif  // WORKER_H_
