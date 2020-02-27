#include <SPI.h>
#include <WiFi101.h>
#include <WiFiUdp.h>
#include <AccelStepper.h>
#include <Servo.h>

Servo myservo0;
Servo myservo1;
Servo myservo2;
int pos_a = 0; 
int pos_b = 0; 
int pos_c = 0; 

AccelStepper stepper1(AccelStepper::DRIVER, 5, 4); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper2(AccelStepper::DRIVER, 10, 9);
AccelStepper stepper3(AccelStepper::DRIVER, 7, 6);

const int ms3Pin   = 11;   // Ms3
const int ms2Pin   = 12;   // Ms2
const int ms1Pin   = 13;   // Ms1

//Initialising variables for motor control
float rover_radius = 14.3;
float wheel_radius = 5;
float wheel_perimeter = wheel_radius * 2 * PI;
float constant_linearVelocity = 0;
float accel = 0;
float accel_x = 0;
float accel_y = 0;
float accel_f = 0;
float accel_n = 0;
float accel_0 = 0;
float accel_1 = 0;
float accel_2 = 0;
float spin = 0;
float dx = 0;
float dy = 0;
float phi = 0 / 180 * PI;
float dphi = 0;
float w = 0;
float v = 0;
float v_n = 0;
float v_x = 0;
float v_y = 0;
float v0 = 0;
float v1 = 0;
float v2 = 0;
float pos_0 = 0;
float pos_1 = 0;
float pos_2 = 0;
float time_limit = 0;
float time_accel = 0;

//WIFI Status
int status = WL_IDLE_STATUS;

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "EEELAB";        // your network SSID (name)
char pass[] = "@adelaide";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

unsigned int localPort = 2390;      // local port to listen on

char packetBuffer[255]; //buffer to hold incoming packet
char ReplyBuffer[] = "acknowledged";       // a string to send back

int DOFs = 8;

WiFiUDP Udp;

void setup() {

  myservo0.attach(1);
  myservo0.write(pos_a);
  myservo1.attach(2);
  myservo1.write(pos_b);
  myservo2.attach(3);
  myservo2.write(pos_c);
  
  // Setting stepper mode (Quarter Step)
  pinMode(ms3Pin, OUTPUT);
  pinMode(ms2Pin, OUTPUT);
  pinMode(ms1Pin, OUTPUT);

  digitalWrite(ms1Pin, LOW);
  digitalWrite(ms2Pin, HIGH);
  digitalWrite(ms3Pin, LOW);

  // Initialize serial:
  Serial.begin(9600);


  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWiFiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  Udp.begin(localPort);
  
  
}

void loop() {

  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remoteIp = Udp.remoteIP();
    Serial.print(remoteIp);
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) packetBuffer[len] = 0;

    String s = packetBuffer;

    int Package[DOFs];

    for (int i = 0; i < DOFs - 1; i++)
    {
      int brk = s.indexOf(",");
      String tString = s.substring(0, brk);
      Package[i] = tString.toInt();
      s.remove(0, brk + 1);
    }
    Package[DOFs - 1] = s.toInt();

    // UDP server
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();

    // Assigning all Packages
    dx = Package[0];  //in cm
    dy = Package[1];  //in cm
    constant_linearVelocity = Package[2];   //in cm/s
    accel = Package[3];   //in cm/s^2
    spin = Package[4];    //in degree
    pos_a = Package[5];
    pos_b = Package[6];
    pos_c = Package[7];

    if (accel==0)
    accel = 5;

    // Equations start getting ugly
    // Speed
    if (dx == 0 && dy == 0)
    {
      time_limit = (spin / 360) * rover_radius * 2 * PI  / constant_linearVelocity;
      
      v0 = constant_linearVelocity;   //in cm/s
      v1 = constant_linearVelocity;   //in cm/s
      v2 = constant_linearVelocity;   //in cm/s

      v0 = v0 / wheel_perimeter * 800;    //in steps/s
      v1 = v1 / wheel_perimeter * 800;    //in steps/s
      v2 = v2 / wheel_perimeter * 800;    //in steps/s
    }
    else
    {
      time_limit = sqrt(dx * dx + dy * dy) / constant_linearVelocity;

      dphi = spin / 180 * PI;
      v_x = dx / time_limit;
      v_y = dy / time_limit;
      w = dphi / time_limit;

      v   =  v_x * cos(phi) + v_y * sin(phi);
      v_n = -v_x * sin(phi) + v_y * cos(phi);

      v0 = -v * sin(PI / 3) + v_n * cos(PI / 3) + w * rover_radius;   //in cm/s
      v1 =                  - v_n               + w * rover_radius;   //in cm/s
      v2 =  v * sin(PI / 3) + v_n * cos(PI / 3) + w * rover_radius;   //in cm/s

      v0 = v0 / wheel_perimeter * 800;    //in steps/s
      v1 = v1 / wheel_perimeter * 800;    //in steps/s
      v2 = v2 / wheel_perimeter * 800;    //in steps/s
    }


    // Acceleration
    if (dx == 0 && dy == 0)
    {
      accel_0 =  accel;   //in cm/s^2
      accel_1 =  accel;   //in cm/s^2
      accel_2 =  accel;   //in cm/s^2

      accel_0 = accel_0 / wheel_perimeter * 800;    //in steps/s^2
      accel_1 = accel_1 / wheel_perimeter * 800;    //in steps/s^2
      accel_2 = accel_2 / wheel_perimeter * 800;    //in steps/s^2
    }
    else
    {
      time_accel = constant_linearVelocity / accel;
      
      accel_x = v_x / time_accel;
      accel_y = v_y / time_accel;

      accel_f =  accel_x * cos(phi) + accel_y * sin(phi);
      accel_n = -accel_x * sin(phi) + accel_y * cos(phi);

      accel_0 = -accel_f * sin(PI / 3) + accel_n * cos(PI / 3);   //in cm/s^2
      accel_1 =                        - accel_n              ;   //in cm/s^2
      accel_2 =  accel_f * sin(PI / 3) + accel_n * cos(PI / 3);   //in cm/s^2

      accel_0 = accel_0 / wheel_perimeter * 800;    //in steps/s^2
      accel_1 = accel_1 / wheel_perimeter * 800;    //in steps/s^2
      accel_2 = accel_2 / wheel_perimeter * 800;    //in steps/s^2
      
    }

    pos_0 = v0 * time_limit;    //in steps
    pos_1 = v1 * time_limit;    //in steps
    pos_2 = v2 * time_limit;    //in steps

    myservo0.write(pos_a);
    myservo1.write(pos_b);
    myservo2.write(pos_c);
    
    // Ends of formula
//    Serial.println("speeds: ");
//    Serial.println(v0);
//    Serial.println(v1);
//    Serial.println(v2);
//
//    Serial.println("accelerations: ");
//    Serial.println(accel_0);
//    Serial.println(accel_1);
//    Serial.println(accel_2);
//    
//    Serial.println("positions: ");
//    Serial.println(pos_0);
//    Serial.println(pos_1);
//    Serial.println(pos_2);
//    
    // Driving Motors
    // Set the current position to 0:
    stepper1.setCurrentPosition(0);
    stepper2.setCurrentPosition(0);
    stepper3.setCurrentPosition(0);

    // Set speeds & accelerations
    stepper1.setMaxSpeed(v0);
    stepper1.setAcceleration(accel_0);
    stepper1.moveTo(pos_0);
    
    stepper2.setMaxSpeed(v1);
    stepper2.setAcceleration(accel_1);
    stepper2.moveTo(pos_1);
    
    stepper3.setMaxSpeed(v2);
    stepper3.setAcceleration(accel_2);
    stepper3.moveTo(pos_2); 

    // Run motors:
    while (abs(stepper1.currentPosition()) < floor(abs(pos_0)))
    {
    stepper1.run();
    stepper2.run();
    stepper3.run();
    }
    
  }
}


void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
