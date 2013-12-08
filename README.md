### Usage

cat ~/.ssh/known_hosts | awk -F'[, ]' '{print $1}' | ./bin/nre
