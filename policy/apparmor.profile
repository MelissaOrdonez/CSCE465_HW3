#include <tunables/global>

/home/ubuntu/csce465-agentsec/hw3/CSCE465_HW3/src/legacy_log_parser {
  #include <abstractions/base>

  /home/ubuntu/csce465-agentsec/hw3/CSCE465_HW3/payload.bin r,

  /home/ubuntu/csce465-agentsec/hw3/CSCE465_HW3/markers/ rw,
  /home/ubuntu/csce465-agentsec/hw3/CSCE465_HW3/markers/** rw,

  audit deny /opt/agentsec/decoy.txt rwklx,

  deny /bin/sh x,
  deny /bin/bash x,
  deny /usr/bin/dash x,
}
