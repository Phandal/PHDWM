song() {
  ncmpcpp --current-song -q | awk '{printf $3}'
}

while true; do

  sleep 1 && printf "$(song)"
done
