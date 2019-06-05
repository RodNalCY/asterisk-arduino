#!/usr/bin/php -q

<?php

require("phpagi.php");
$agi = new AGI();

// Pon la ip de arduino
$arduino_ip = "tcp://192.168.0.104";
$arduino_port = 80;


//open a socket to the Arduino's IP address and port

$fp = fsockopen($arduino_ip, $arduino_port, $errno, $errstr);





if (!$fp) {
   exit();
}

$continue = true;
while($continue){
     if (($return['result'] >= 0) and ($return['result'] <= 9)){
      $ascii = chr('1'); //convert that # to ASCII
      fwrite($fp, $ascii); //La tecla pulsada se envia al Arduino
exit();
   }

}

fclose($fp);

?>