#include <mf_aqm_ch2o.h>

float concentration = 0.0;
mf_aqm_ch2o ch2o;//串口输入格式:FF FF 01 22 5A 05 03 05 00 00 03 05 DD,其中22 5A为有效数据，22是高位，5A是地位，代表气体浓度(0x22*256+0x5A)/1000 = 23.045mg/m3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  ch2o.loop();
  if (concentration != ch2o.read())
  {
      u16 temp;
      concentration = ch2o.read();
      temp = concentration*1000;
      Serial.print("CH2O Gas Concentration: ");
      Serial.print(temp/1000);
      temp %= 1000;
      Serial.write('.');
      Serial.print(temp/100);
      temp %= 100;
      Serial.print(temp/10);
      temp %= 10;
      Serial.print(temp);
      Serial.print("mg/m3");
      Serial.write(0x0A);
  }
  
}