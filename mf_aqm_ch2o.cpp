/**
  ******************************************************************************
  * @file   	mf_aqm_ch2o.cpp
  * @author   	Jack
  * @version	1.0
  * @date		2015-11-26
  * @brief		MF_AQM_CH2O甲醛传感器模块驱动
  * 
  * Discription:
  ******************************************************************************
  */
#include "arduino.h"
#include "stdio.h"
#include "mf_aqm_ch2o.h"
#if SOFTWARE_SERIAL
#include "SoftwareSerial.h"
#endif

#if SOFTWARE_SERIAL
SoftwareSerial uart(__RX_PIN__, __TX_PIN__);
#else
Serial uart();
#endif


typedef struct
{
    byte rx_buffer[20];     //接收数据缓存
	u8   rx_posi;        //当前接收数据字节数
    float concentration;    //气体浓度
}param_t;

static param_t param = {{0}, 0, 0.0};


mf_aqm_ch2o::mf_aqm_ch2o( void )
{ 
	uart.begin(9600);	
    //uart.println("mf_aqm_ch2o");
}

void mf_aqm_ch2o::loop( void )
{
    if (uart.available() > 0)
    {
        char dat = uart.read();
        static unsigned long time = millis();

        if (millis() - time > 500)
        {
            u8 i;
            param.rx_posi = 0;
            for (i = 0; i < sizeof(param.rx_buffer); i++)
            {
                param.rx_buffer[0] = 0;
            }
        }
        
        time = millis();

        param.rx_buffer[param.rx_posi++] = dat;

        if (param.rx_posi > 12)
        {
            u8 i;
            if ((param.rx_buffer[0] == 0xFF)
                && (param.rx_buffer[1] == 0xFF)
                && (param.rx_buffer[12] == 0xDD))
            {
                param.concentration = 
                    (param.rx_buffer[4]*256+param.rx_buffer[5])*0.001;
            }
            param.rx_posi = 0;
            for (i = 0; i < sizeof(param.rx_buffer); i++)
            {
                param.rx_buffer[0] = 0;
            }
        }
    }
}

//read CH2O gas concentration
float mf_aqm_ch2o::read( void )
{
    return 	param.concentration;
}
