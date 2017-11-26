// Usage:
// ./main -type=<cpu|io|balanced> -coroutines=<n> -threads=<m>
//
// Time this program:
// $ time ./coroutine -type=cpu -coroutines=5 -threads=2

#define BOOST_COROUTINES_NO_DEPRECATION_WARNING 1

#include <functional>
#include <iostream>
#include <string>
#include <cstdio>
#include <thread>
#include <vector>

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>

#include "worker.h"

#include <gflags/gflags.h>

namespace {

namespace asio = boost::asio;

using std::string;
using std::shared_ptr;
using std::placeholders::_1;
using asio::io_service;
using coen::Worker;
using coen::Progress;

DEFINE_string(type, "", "cpu|io|balanced");
DEFINE_int32(coroutines, 0, "the number of concurrent coroutines");
DEFINE_int32(threads, 0, "the number of underlying threads");

void ValidateFlags() {
  const string& t = FLAGS_type;
  if ((t != "cpu" && t != "io" && t != "balanced") ||
      FLAGS_coroutines <= 0 || FLAGS_threads <= 0) {
    std::puts("Invalid flags!");
    std::puts("Usage Example: ./coroutine -type=io -coroutines=4 -threads=2");
    std::exit(1);
  }
}

}  // namespace

constexpr int kNumTasks = 2048;

int main(int argc, char* argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  ValidateFlags();

  auto request = FLAGS_type + "\n";
  auto io_svc = std::make_shared<io_service>();
  auto progress = std::make_shared<Progress>(kNumTasks);

  // Spawn the coroutines.
  for (int i = 0; i < FLAGS_coroutines; i++) {
    auto worker = std::make_shared<Worker>(io_svc, request, progress);
    asio::spawn(*io_svc, std::bind(&Worker::Run, worker, _1));
  }

  // Create the thread pool.
  std::vector<std::thread> threads;
  for (int i = 0; i < FLAGS_threads; i++) {
    threads.push_back(std::thread([=]{ io_svc->run(); }));
  }
  for (auto& thread : threads) {
    thread.join();
  }
}
