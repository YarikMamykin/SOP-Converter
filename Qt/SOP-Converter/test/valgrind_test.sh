#!/bin/bash

cd ../../build-openFOAM-configurator-Debug
valgrind \
--tool=memcheck \
--leak-check=full \
--show-reachable=yes \
--show-possibly-lost=no \
--track-origins=yes \
--xml=yes \
--xml-file="valgrind-test-result.xml" -v ./openFOAM-configurator

