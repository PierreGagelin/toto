#!/usr/bin/env sh

set -eu

gcc -o /rest-app /code/rest_app.c -lulfius -ljansson
