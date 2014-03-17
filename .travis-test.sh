
function die() {
  echo "ERROR: $1"
  exit 1
}

if [[ $OSSEC_TYPE == "all" ]]; then 
  cp ./etc/travis-preloaded-vars.conf ./etc/preloaded-vars.conf || die "create preloaded-vars.conf failed"
  sudo ./install.sh || die "sudo ./install.sh: Failed"
  (cd contrib/ossec-testing && sudo python runtests.py ) || die"runtests failed"
else 
  exit 0
fi
