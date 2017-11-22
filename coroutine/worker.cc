#include "worker.h"

#include <iostream>
#include <cinttypes>
#include <cstdlib>

namespace coen {

namespace {

namespace asio = boost::asio;

using std::string;
using std::cout;
using std::endl;

using boost::asio::ip::tcp;
using asio::yield_context;

}  // namespace

Worker::Worker(std::shared_ptr<boost::asio::io_service> io_service,
               std::string request,
               std::shared_ptr<Progress> progress)
    : io_service_(io_service),
      request_(request),
      progress_(progress) {
}

void Worker::Run(yield_context yield) {
  while (progress_->FetchTask()) {
    DoTask(yield);
    progress_->ReportTaskDone();
  }
}

void Worker::DoTask(yield_context yield) {
  boost::system::error_code ec;
  tcp::socket socket(*io_service_);

  tcp::resolver::query query("localhost", "8000");
  tcp::resolver resolver(*io_service_);
  auto iterator = resolver.async_resolve(query, yield[ec]);
  assert(!ec);

  asio::async_connect(socket, iterator, yield[ec]);
  assert(!ec);

  asio::async_write(socket, asio::buffer(request_), yield[ec]);
  assert(!ec);

  asio::streambuf buf;
  asio::async_read(socket, buf, asio::transfer_at_least(1), yield[ec]);
  assert(!ec);

  // Skip the header part
  std::istream in(&buf);
  int amount;
  in >> amount;

  std::int64_t sum = 0;
  for (int i = 1; i <= amount; ++i) {
    sum += (amount - i) / 3;
  }

  // Make sure the calculation of `sum` will not be pruned by the compiler.
  if (sum < 0) {
    std::exit(1);
  }
}

}  // namespace coen
