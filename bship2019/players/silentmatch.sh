../master/master -a -n > output &
sleep 1
./player > output &
sleep 1
../sample/sweep > output &

