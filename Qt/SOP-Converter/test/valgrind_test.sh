#!/bin/bash


VAL_DIR="$PWD"
cd ../../build-SOP-Converter-Desktop-Debug
valgrind \
--tool=memcheck \
--leak-check=full \
--show-reachable=yes \
--show-possibly-lost=no \
--track-origins=yes \
--gen-suppressions=no \
--suppressions="${VAL_DIR}/valgrind.sup" \
--xml=yes \
--xml-file="${VAL_DIR}/valgrind-test-result.xml[$(date)]" -v ./SOP-Converter

