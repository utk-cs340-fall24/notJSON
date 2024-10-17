#!/bin/bash

gcc -o bin/server src/serverTest.c lib/server.c
gcc -o bin/client src/clientTest.c lib/server.c
