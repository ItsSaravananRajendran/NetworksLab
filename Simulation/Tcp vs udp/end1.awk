BEGIN {
 seqno = -1; 
 droppedPackets = 0;
 receivedPackets = 0;
 count = 0;
 }

$0 ~/^+.* CBR/ {
         start_time[$41] = $3;
}

  

 $0 ~/^-.* CBR/ {
 		time = -1*(start_time[$41] - $3);
 		printf "%d %f\n", $41,time;
         
 }

 END{

 }