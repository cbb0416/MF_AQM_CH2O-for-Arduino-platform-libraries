/*!
 * @file    mf_aqm_ch2o.h
 * @brief
 *
 * \n
 * @details
 *
 * \n
 * @version 1.0
 * @author  Jack
 * @date    2015-11-26
 *
 * @history
 *
 */
#ifndef __MF_AQM_CH2O_H__
#define __MF_AQM_CH2O_H__

#define SOFTWARE_SERIAL     1
#if SOFTWARE_SERIAL
#define HARDWARE_SERIAL     0
#else
#define HARDWARE_SERIAL     1
#endif

#if SOFTWARE_SERIAL
#define __RX_PIN__          12
#define __TX_PIN__          13
#endif

class mf_aqm_ch2o
{
	public :
		mf_aqm_ch2o( void );	
		void loop( void );
        float read_current( void );
		float read_average( void );
};



#endif  /*__MF_AQM_CH2O_H__*/
