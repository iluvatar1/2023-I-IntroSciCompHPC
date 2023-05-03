# file: script.sh
echo "First arg: ${1}"
timeout 10s stress -t 10s -c 1 # stress one core
echo "Stress test done"
