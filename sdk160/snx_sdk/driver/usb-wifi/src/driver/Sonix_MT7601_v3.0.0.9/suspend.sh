count=1

while [ "$count" != "10000000" ]
do
echo $count
echo auto > /sys/bus/usb/devices/2-1.2/power/level
sleep 10
echo on > /sys/bus/usb/devices/2-1.2/power/level
sleep 10
count=$(($count + 1))
done
