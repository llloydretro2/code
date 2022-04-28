#/bin/bash

./ecs36b_hw1_client 169.237.6.102 95601 '{"action": "ecs36b_hw2", "sID": "918158439", "avatar_name": "Amon", "code: "1266235189", "srcIP": "128.120.237.90", "latitude": "38.544", "longitude": "-121.740", "ifconfig_srcIP": "168.150.24.407", "NAT": "yes"}' > return.text

cat return.text
