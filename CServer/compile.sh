#!/bin/bash

gcc -o bin/test src/serverTest.c lib/server.c 
gcc -o bin/clientTest src/clientTest.c lib/server.c 
