#include <GSM_MQTT.h>

//#include "GSM_MQTT.h"
#include <SoftwareSerial.h>
#define my_topic_name "dbox"
String MQTT_HOST = "182.163.112.205";
unsigned char msg;
unsigned char nc=0;
/*
   MQTT host address
*/
String MQTT_PORT = "1883";
/*
   MQTT port
*/
SoftwareSerial mySerial(10, 11); // RX, TX
/*
   Software Serial through which mqtt events log is printed at 9600 baud rate
*/
void GSM_MQTT::AutoConnect(void)
{
  /*
     Use this function if you want to use autoconnect(and auto reconnect) facility
     This function is called whenever TCP connection is established (or re-established).
     put your connect codes here.
  */
  connect("qwertyuiop", 0, 0, "", "", 1, 0, 0, 0, "", "");
  /*    void connect(char *ClientIdentifier, char UserNameFlag, char PasswordFlag, char *UserName, char *Password, char CleanSession, char WillFlag, char WillQoS, char WillRetain, char *WillTopic, char *WillMessage);
          ClientIdentifier  :Is a string that uniquely identifies the client to the server.
                            :It must be unique across all clients connecting to a single server.(So it will be better for you to change that).
                            :It's length must be greater than 0 and less than 24
                            :Example "qwerty"
          UserNameFlag      :Indicates whether UserName is present
                            :Possible values (0,1)
                            :Default value 0 (Disabled)
          PasswordFlag      :Valid only when  UserNameFlag is 1, otherwise its value is disregarded.
                            :Indicates whether Password is present
                            :Possible values (0,1)
                            :Default value 0 (Disabled)
          UserName          :Mandatory when UserNameFlag is 1, otherwise its value is disregarded.
                            :The UserName corresponding to the user who is connecting, which can be used for authentication.
          Password          :alid only when  UserNameFlag and PasswordFlag are 1 , otherwise its value is disregarded.
                            :The password corresponding to the user who is connecting, which can be used for authentication.
          CleanSession      :If not set (0), then the server must store the subscriptions of the client after it disconnects.
                            :If set (1), then the server must discard any previously maintained information about the client and treat the connection as "clean".
                            :Possible values (0,1)
                            :Default value 1
          WillFlag          :This flag determines whether a WillMessage published on behalf of the client when client is disconnected involuntarily.
                            :If the WillFlag is set, the WillQoS, WillRetain, WillTopic, WilMessage fields are valid.
                            :Possible values (0,1)
                            :Default value 0 (Disables will Message)
          WillQoS           :Valid only when  WillFlag is 1, otherwise its value is disregarded.
                            :Determines the QoS level of WillMessage
                            :Possible values (0,1,2)
                            :Default value 0 (QoS 0)
          WillRetain        :Valid only when  WillFlag is 1, otherwise its value is disregarded.
                            :Determines whether the server should retain the Will message.
                            :Possible values (0,1)
                            :Default value 0
          WillTopic         :Mandatory when  WillFlag is 1, otherwise its value is disregarded.
                            :The Will Message will published to this topic (WillTopic) in case of involuntary client disconnection.
          WillMessage       :Mandatory when  WillFlag is 1, otherwise its value is disregarded.
                            :This message (WillMessage) will published to WillTopic in case of involuntary client disconnection.
  */
  
}
void GSM_MQTT::OnConnect(void)
{
  /*
     This function is called when mqqt connection is established.
     put your subscription publish codes here.
  */
  msg= _generateMessageID();
  //subscribe(0,msg, my_topic_name, 1);
  /*    void subscribe(char DUP, unsigned int MessageID, char *SubTopic, char SubQoS);
          DUP       :This flag is set when the client or server attempts to re-deliver a SUBSCRIBE message
                    :This applies to messages where the value of QoS is greater than zero (0)
                    :Possible values (0,1)
                    :Default value 0
          Message ID:The Message Identifier (Message ID) field
                    :Used only in messages where the QoS levels greater than 0 (SUBSCRIBE message is at QoS =1)
          SubTopic  :Topic names to which  subscription is needed
          SubQoS    :QoS level at which the client wants to receive messages
                    :Possible values (0,1,2)
                    :Default value 0
  */

 // publish(0, 0, 0, msg, my_topic_name, "abdur rahman");
  /*  void publish(char DUP, char Qos, char RETAIN, unsigned int MessageID, char *Topic, char *Message);
      DUP       :This flag is set when the client or server attempts to re-deliver a PUBLISH message
                :This applies to messages where the value of QoS is greater than zero (0)
                :Possible values (0,1)
                :Default value 0
      QoS       :Quality of Service
                :This flag indicates the level of assurance for delivery of a PUBLISH message
                :Possible values (0,1,2)
                :Default value 0
      RETAIN    :if the Retain flag is set (1), the server should hold on to the message after it has been delivered to the current subscribers.
                :When a new subscription is established on a topic, the last retained message on that topic is sent to the subscriber
                :Possible values (0,1)
                :Default value 0
      Message ID:The Message Identifier (Message ID) field
                :Used only in messages where the QoS levels greater than 0
      Topic     :Publishing topic
      Message   :Publishing Message
  */
}
void GSM_MQTT::OnMessage(char *Topic, int TopicLength, char *Message, int MessageLength)
{
  
  /*
    This function is called whenever a message received from subscribed topics
    put your subscription publish codes here.
  */

  /*
     Topic        :Name of the topic from which message is coming
     TopicLength  :Number of characters in topic name
     Message      :The containing array
     MessageLength:Number of characters in message
  */
   mySerial.println(TopicLength);
  mySerial.println(Topic);
  mySerial.println(MessageLength);
  mySerial.println(Message);
//publish(0, 0, 0, _generateMessageID(), "my_topic_name", "abdur rahman");

}
GSM_MQTT MQTT(20);
/*
   20 is the keepalive duration in seconds
*/
//......................................MQ4.sensor's...............................
int gas_sensor = A0; //Sensor pin
float m = -0.36; //Slope
float b = 1.1029; //Y-Intercept
float R0 =75; //Sensor Resistance in fresh air from previous code


void setup()
{
  // GSM modem should be connected to Harware Serial
  MQTT.begin(); // initialize mqtt:
  pinMode(gas_sensor, INPUT); //Set gas sensor as input
}
void loop()
{

  if (MQTT.available())
  {
     delay(3000);
  //......................starting MQ4 sensor's operation ........................
  //http://www.geekstips.com/mq4-sensor-natural-gas-methane-arduino/
  //datasheet https://www.sparkfun.com/datasheets/Sensors/Biometric/MQ-4.pdf
   float sensor_volt; //Define variable for sensor voltage
  float RS_gas; //Define variable for sensor resistance
  float ratio; //Define variable for ratio
  float sensorValue =analogRead(gas_sensor); //Read analog values of sensor
  sensor_volt = sensorValue * (5.0 / 1023.0); //Convert analog values to voltage
  RS_gas = ((5.0 * 10.0) / sensor_volt) - 10.0; //Get value of RS in a gas
  ratio = RS_gas / R0;   // Get ratio RS_gas/RS_air

  float ppm_log = (log10(ratio) - b) / m; //Get ppm value in linear scale according to the the ratio value
  float ppm = pow(10, ppm_log); //Convert ppm value to log scale
  float percentage =ppm / 10000; //Convert to percentage
     //......................ended MQ4 sensor's operation ........................
     
 MQTT.publish(0, 0, 0, msg, my_topic_name,json(ppm,percentage));
  delay(500);
  }
    
  MQTT.processing();
 
}
char* json( float ppm, float percentage )
{
      /////.......................JSON Formating...............
    char ppma[10];
    char percentagea[10];
    dtostrf(ppm,6,3,ppma);
    dtostrf(percentage,6,3,percentagea);


    char mqtt_json_packet[60];
    strcpy(mqtt_json_packet, "{\"ppm\":");
    strcat(mqtt_json_packet, ppma);
    strcat(mqtt_json_packet, ",\"perc\":");
    strcat(mqtt_json_packet, percentagea);
    strcat(mqtt_json_packet, ",\"ltime\":\"03:12:56\"}");
    /////.......................JSON Formating...............
    return mqtt_json_packet;
}


