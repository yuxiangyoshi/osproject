#!/usr/bin/env bash
set -e

cd build
make
cp coroutine ../coroutine_osx64
