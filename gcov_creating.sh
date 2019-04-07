#!/bin/bash
lcov --directory main.gcda --capture --output-file gcov_main.info
genhtml -o ./gcov_info/main ./gcov_main.info

lcov --directory input.gcda --capture --output-file gcov_input.info
genhtml -o ./gcov_info/input ./gcov_input.info

lcov --directory output.gcda --capture --output-file gcov_output.info
genhtml -o ./gcov_info/output ./gcov_output.info

lcov --directory analysing.gcda --capture --output-file gcov_analysing.info
genhtml -o ./gcov_info/analysing ./gcov_analysing.info

lcov --directory input.gcda --capture --output-file gcov_input.info
genhtml -o ./gcov_info/input ./gcov_input.info
