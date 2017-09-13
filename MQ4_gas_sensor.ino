
int gas_sensor = A0; //Sensor pin
float m = -0.301; //Slope
float b = 1; //Y-Intercept
float R0 = 10; //Sensor Resistance in fresh air from previous code

void setup() {
  Serial.begin(9600); //Baud rate
 
  pinMode(gas_sensor, INPUT); //Set gas sensor as input
}

void loop() {
 
  float sensor_volt; //Define variable for sensor voltage
  float RS_gas; //Define variable for sensor resistance
  float ratio; //Define variable for ratio
  float sensorValue = analogRead(gas_sensor); //Read analog values of sensor
  sensor_volt = sensorValue * (5.0 / 1023.0); //Convert analog values to voltage
  RS_gas = ((5.0 * 10.0) / sensor_volt) - 10.0; //Get value of RS in a gas
  ratio = RS_gas / R0;   // Get ratio RS_gas/RS_air

  double ppm_log = (log10(ratio) - b) / m; //Get ppm value in linear scale according to the the ratio value
  double ppm = pow(10, ppm_log); //Convert ppm value to log scale
  double percentage = ppm / 10000; //Convert to percentage
  Serial.println("sensor value: "+String(sensorValue));
  Serial.println("       Rs/R0: "+String(ratio));
  Serial.println("sensor   ppm: "+String(ppm));
  Serial.println("  percentage: "+String(percentage));
  char *mqtt_data="\'{\"sensorValue\":"+char(sensorValue);//+",\"PPM\":"+String(ppm)+",\"percentage\":"+String(percentage)+"}\'";
  Serial.println(String(mqtt_data));
delay(3000);
}
