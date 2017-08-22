set val(chan)           Channel/WirelessChannel    ;
set val(prop)           Propagation/FreeSpace	   ;
set val(mac)            Mac/802_11                 ;
set val(ifq)            Queue/DropTail/PriQueue    ;
set val(ll)             LL                         ;
set val(ant)            Antenna/OmniAntenna        ;
set val(ifqlen)         50                         ;
set val(nn)             5         		   ;
set val(rp)             AODV                       ;
set val(x)              2000   			   ;
set val(y)              2000   			   ;
set val(netif)          Phy/WirelessPhy            ;

set ns [new Simulator]

set tracefd [open ran.tr w]
set namtrace [open ran.nam w]
set dist [open distance.tr w]

$ns trace-all $tracefd
$ns namtrace-all-wireless $namtrace $val(x) $val(y)

set topo [new Topography]
$topo load_flatgrid $val(x) $val(y)

create-god $val(nn)

###########

$ns node-config 	 -adhocRouting $val(rp) \
			 -llType $val(ll) \
			 -macType $val(mac) \
			 -ifqType $val(ifq) \
			 -ifqLen $val(ifqlen) \
			 -antType $val(ant) \
			 -propType $val(prop) \
			 -phyType $val(netif) \
			 -channelType $val(chan) \
			 -topoInstance $topo \
			 -agentTrace ON \
#			 -routerTrace ON \
#			 -macTrace OFF \
			 -movementTrace ON 


$val(netif) set CPThresh_ 10.0
$val(netif) set CSThresh_ 2.78831e-9    ;#100m
$val(netif) set RXThresh_ 1.11532e-8    ;#50m
$val(netif) set bandwidth_ 1Mb
$val(netif) set Pt_ 0.2818
$val(netif) set freq_ 2.4e+9
$val(netif) set L_ 1.0

Antenna/OmniAntenna set X_ 0
Antenna/OmniAntenna set Y_ 0
Antenna/OmniAntenna set Z_ 0.25
Antenna/OmniAntenna set Gt_ 1
Antenna/OmniAntenna set Gr_ 1

###################

for {set i 0} {$i < $val(nn)} {incr i} {
set n($i) [$ns node]
}


$n(0) set X_ 1000
$n(0) set Y_ 1000
$n(0) set Z_ 0.0
$ns initial_node_pos $n(0) 50
$ns at 0.0 "$n(0) label Cell-Tower"



###### Mobile Nodes

for {set i 1} {$i < 5} {incr i} {
$n($i) color blue
$ns at 0.0 "$n($i) label Mobile-($i)"
$ns initial_node_pos $n($i) 20
$ns at 0.0 "$n($i) color blue"
}

proc rand {} {

global ns n
set time 1.0
set now [$ns now]
for {set i 1} {$i < 5} {incr i} {
	set xx [expr rand()*1500]
	set yy [expr rand()*1500]
	$n($i) set X_ $xx
	$n($i) set Y_ $yy
	$n($i) set Z_ 0.0
	$ns at $now "$n($i) setdest $xx $yy 50.0"
	}
$ns at [expr $now+$time] "rand"
}




$ns at 0.0 "rand"


########### Distance and RSS Calculation

proc distrss {} {

global x1 x2 y1 y2 d n i j ns dist

for {set i 0} {$i < 1} {incr i} {
   for {set j 1} {$j < 5} {incr j} {

if {$i != $j && $i < $j} {
set x1 [expr int([$n($i) set X_])]
set y1 [expr int([$n($i) set Y_])]
set x2 [expr int([$n($j) set X_])]
set y2 [expr int([$n($j) set Y_])]
set d [expr int(sqrt(pow(($x2-$x1),2)+pow(($y2-$y1),2)))]


puts $dist "--------------------------"
puts $dist "Distance between node Cell Tower $i and Mobile-$j = $d "


}}}}



$ns at 0 "distrss"
$ns at 5 "distrss"
$ns at 10 "distrss"
$ns at 15 "distrss"
$ns at 20 "distrss"
$ns at 25 "distrss"
$ns at 30 "distrss"






proc tcpdata {} {

global n i j ns 

for {set i 0} {$i < 1} {incr i} {
   for {set j 1} {$j < 5} {incr j} {

if {$i != $j && $i < $j} {
set tcp [new Agent/TCP]
$tcp set class_ 2
$ns attach-agent $n($j) $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n($i) $sink
$ns connect $tcp $sink
$tcp set fid_ 1

#Setup a FTP over TCP connection
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP



$ns at 1.0 "$ftp start"
$ns at 30 "$ftp stop"
}}}}

$ns at 0 "tcpdata"


proc stop {} {
global ns tracefd namtrace dist
$ns flush-trace
close $tracefd
close $namtrace
close $dist
exec nam ran.nam &
exit 0
}

$ns at 30 "stop"

$ns run
