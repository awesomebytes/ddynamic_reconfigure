#!/usr/bin/env bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )" # gets the current dir
PKG=$(cd ${DIR}/..; printf %s "$PWD") # gets this ROS pkg path

for test in $(find ${DIR} -name *.test -printf '%f\n'); do # finds the test file names
    rostest ${PKG##*/} ${test} # executes the tests
done