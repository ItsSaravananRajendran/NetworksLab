BEGIN {

         sendLine = 0;

         recvLine = 0;

         fowardLine = 0;

 }

  

 if($5 == "cbr" &;& $1 == "+") {
	sendLine++;
 } else if(($7 == "cbr") && ($1 == "r")) {
 recvLine++;
 printf "%d %.4f\n" ,$3, (recvLine/sendLine);
 }


 END {


}

 