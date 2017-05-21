count=1

while [ "$count" != "10000000" ]
do
	./unload
	./load
	echo $count
	sleep 20
	count=$(($count + 1))
done
