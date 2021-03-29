#!/bin/bash

# ./ip

# ./main trafficvideo.mp4 0

# for i in 5 10 15 20 25 30
# do
#    ./main trafficvideo.mp4 1 $i
# done

# ./main trafficvideo.mp4 2

# ./main trafficvideo.mp4 3 1280 720
# ./main trafficvideo.mp4 3 720 576
# ./main trafficvideo.mp4 3 640 360
# ./main trafficvideo.mp4 3 320 180

# for i in {1..9}
# do
#    ./main trafficvideo.mp4 4 $i
# done

# for i in {1..9}
# do
#    ./main trafficvideo.mp4 5 $i
# done

cd ..
cd analysis
cd utility
for i in {1..9}
do
   python3 method4.py --n $i
   python3 method5.py --n $i
done

python3 graph.py --file data

for x in queue dynamic both
do
    python3 method1_graph.py --type $x
    python3 method3_graph.py --type $x
    python3 method4_graph.py --type $x
    python3 method5_graph.py --type $x
done

for x in queue dynamic both
do
   python3 utility.py --type $x
done
