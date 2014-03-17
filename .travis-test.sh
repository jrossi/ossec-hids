

if [[ $OSSEC_TYPE == "all" ]]; then 
  cp ./etc/travis-preloaded-vars.conf ./etc/preloaded-vars.conf || echo "ERROR: create preloaded-vars.conf failed" && exit 1
  sudo ./install.sh || echo "ERROR: sudo ./install.sh: Failed" && exit 1
  (cd contrib/ossec-testing && sudo python runtests.py ) || echo "FAILURE: runtests failed" && exit 1
else 
  exit 0
fi
