# COEN283
Course Project of COEN283

## Server

A TCP server.

Valid requests:
- `cpubound`
  Request for a cpu-bound task

- `balanced`
  Request for a cpu-io-balanced task

- `iobound`
  Request for a io-bound task

**NOTE: Please add a `\n` at the end of a request when sending it to the server.**

The response is an positive integer `amount` representing the amount of
computation of the task (with a trailing `\n`). The task is defined as

```
int64_t sum = 0;
for (int i = 1; i <= amount; ++i) {
  sum += (amount - i) / 3;
}
```

## Coroutine

Measure the time cost of the program under various setting:
- `type`
  The type of the task. Can be "cpubound", "iobound" or "balanced".

- `coroutines`
  The number of concurrent coroutines.

- `threads`
  The number of underlying threads.

For example,

```
$ time ./main -type=balanced -coroutines=1 -threads=1
real  0m1.869s
user  0m0.362s
sys   0m0.042s

$ time ./main -type=balanced -coroutines=4 -threads=1
real  0m0.621s
user  0m0.231s
sys   0m0.030s

$ time ./main -type=balanced -coroutines=4 -threads=2
real  0m0.469s
user  0m0.360s
sys   0m0.038s
```

## Python Demo Server

run in two terminals

python localserver.py
python client.py

you would see 3 sets of 10 random integers within certain ranges is distributed from server to client
