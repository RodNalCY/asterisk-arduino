int x;
#include <SPI.h>
#include <Ethernet.h> 
/**
* EN ESTE EJEMPLO USAMOS SHIELD ETHERNET Y OBTENEMOS  
* UNA IP MEDIANTE DHCP
* TEST FINAL
Al llamar al número  2005 se encenderá nuestro led
Al llamar al número  2006 se cual apagará nuestro led
Al llamar al número  2008 se cual hará parpadear a nuestro led
*
*/
//Declaración de la direcciones MAC e IP. También del puerto 80
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; //MAC
//IPAddress ip(192, 168, 0, 115); //IP Cambiar por Tu ip->NO SIRVE
EthernetServer servidor(80);
int PIN_LED7 = 7;
int PIN_LED8 = 8;

void dhcp() {
  // VERIFICAMOS EL ESTADO DE CONEXION DE LA SHIELD SI TODO ESTA BIEN IRA AL 'CASE 4'
  switch (Ethernet.maintain()) {
    case 1:
      //renewed fail
      Serial.println("Error: renewed fail");
      break;

    case 2:
      //renewed success
      Serial.println("Renewed success");
      //print your local IP address:
      Serial.print("My IP address: ");
      Serial.println(Ethernet.localIP());
      break;

    case 3:
      //rebind fail
      Serial.println("Error: rebind fail");
      break;

    case 4:
      //rebind success
      Serial.println("Rebind success");
      //print your local IP address:
      Serial.print("Mi IP address: ");
      Serial.println(Ethernet.localIP());
      break;

    default:
      //nothing happened
      break;
  }
}

void setup() {
 Serial.begin(9600);
  while (!Serial) {
    ; // Esperando un puerto serial para conectarse...
  }

  // Iniciamos la conexion Ethernet con DHCP
  Serial.println("Iniciando Ethernet con DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Conexion Fallida configura DHCP...");
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet no encontrado, Necesita verificar la conexion de su shield  :(");
    } else if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Cable Ethernet no conectado");
    }
    // no point in carrying on, so do nothing forevermore:
    while (true) {
      delay(1);
    }
  }
  // print your local IP address:
  Serial.print("Mi IP address: ");
  Serial.println(Ethernet.localIP());


 

  pinMode(PIN_LED7, OUTPUT); //Declaración del pin de salida2
  digitalWrite(PIN_LED7, 0); //Incialmente apagado
  pinMode(PIN_LED8, OUTPUT); //Declaración del pin de salida7
  digitalWrite(PIN_LED8, 0); //Incialmente apagado

  servidor.begin();
  delay(1000);
  Serial.println("connecting...");


}
void loop() {
  dhcp();
  int a = 2;
  EthernetClient cliente = servidor.available();
  // LED SWITCH CONTROL - ASTERISK
  if (cliente) {
    x = cliente.read(); //Leemos los datos que vienen del ethernet
    Serial.print("conectado: "); //Indicamos conectado por el puerto
    Serial.println(x);
  }
  if (x == 1) {
    Serial.print(x); //Mostramos lo que hemos recibido por TCP/IP
    Serial.println("activo: "); //Informamos por el puerto de serie que activamos el PIN DE SALIDA
    digitalWrite(PIN_LED7, 1); //Activamos el pin de salida del Arduino poniendola a 5V
    a++;
    x = ' ';
  }
  if (x == 2) {
    Serial.print(x); //Mostramos lo que hemos recibido por TCP/IP
    Serial.println("inactivo: "); //Informamos por el puerto de serie que activamos el PIN DE SALIDA
    digitalWrite(PIN_LED7, 0); //Activamos el pin de salida del Arduino poniendola a 5V
    a++;
    x = ' ';
  }
  // PARA EL PARPADEO - ASTERISK
  if (x == 11 && a == 2) {
    Serial.print(x);
    Serial.println("activo: ");
    digitalWrite(PIN_LED8, 1);
    delay(2000);
    Serial.print(x);
    Serial.println("inactivo: ");
    digitalWrite(PIN_LED8, 0);
    delay(1000);
    Serial.print(x);
    Serial.println("activo: ");
    digitalWrite(PIN_LED8, 1);
    delay(2000);
    Serial.print(x);
    Serial.println("inactivo: ");
    digitalWrite(PIN_LED8, 0);
    delay(1000);
    a++;
    x= ' ';
  }
}
