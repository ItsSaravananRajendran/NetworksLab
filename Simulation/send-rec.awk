BEGIN {

         sendLine = 0;

         recvLine = 0;

         fowardLine = 0;

 }

  

 $0 ~/^s.* AGT/ {

         sendLine ++ ;
         printf "%d %.4f\n", $3,(recvLine/sendLine);
 }

  

 $0 ~/^r.* AGT/ {

         recvLine ++ ;
         printf "%d %.4f\n" ,$3, (recvLine/sendLine);
 }


 END {


}

 