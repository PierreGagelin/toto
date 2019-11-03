#!/usr/bin/env sh

cp /code/daemons.conf /etc/frr/daemons
cp /code/zebra.conf /etc/frr/

chown -R frr:frr /etc/frr

service frr start
