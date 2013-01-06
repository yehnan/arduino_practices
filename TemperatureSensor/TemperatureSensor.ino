#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress thermometer;

void setup(void)
{
  Serial.begin(115200);
  Serial.println("Temperature Sensor");
  sensors.begin();
  
  Serial.print("Device Count=");
  Serial.println(sensors.getDeviceCount());
  sensors.getAddress(thermometer, 0);
  
  Serial.print("Valid=");
  Serial.println(sensors.validAddress(thermometer));
  
  Serial.print("Resolution=");
  Serial.println(sensors.getResolution(thermometer));
}

void loop(void)
{
  sensors.requestTemperatures();
  Serial.println(sensors.getTempCByIndex(0));

  delay(1000);
}
