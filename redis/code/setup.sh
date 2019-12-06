#!/usr/bin/env sh

set -eu

redis-server &

gcc -o /client client.c -lhiredis

/client
