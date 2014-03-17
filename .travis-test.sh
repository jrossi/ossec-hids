
function iferrdie() {
  if [[ $1 ne 0  ]]; then 
    echo "ERROR: $2"
    exit $1 
  fi
}

if [[ $OSSEC_TYPE == "All" ]]; then 
  cp ./etc/travis-preloaded-vars.conf ./etc/preloaded-vars.conf || iferrdie($?, "create preloaded-vars.conf failed")
  sudo ./install.sh || iferrdie($?, "sudo ./install.sh: Failed")
  (cd contrib/ossec-testing && sudo python runtests.py ) || iferrdie($?, "runtests failed")
else 
  exit 0
fi
