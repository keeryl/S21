#!/bin/bash

nginx -g "daemon off;"
# service nginx start
nginx -s reload

# while true; do
#     sleep 1
# done