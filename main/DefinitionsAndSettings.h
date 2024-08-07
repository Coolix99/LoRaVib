//define EEPROM adresses
#define allowUniversalTelegramAccess_EEPROM		0   	//0
#define restartOnConnectionFail_EEPROM			1     	//1
#define debugLevel_EEPROM						2     	//1

#define telegramMessageSendTimeout_EEPROM		8     	//30 ???
#define telegramUpdateInterval_EEPROM			9     	//10 sec

#define wifiCredsStartAdress_EEPROM 			20
//all eeprom cells beyond wifiCredsStartAdress_EEPROM are reserved for wifi creds!!!


//define pins
#define Button1_Pin				14
#define Button2_Pin				13
#define Button3_Pin				10
#define ignition_Pin			15
#define vibrationMotor_Pin		8
#define WS2812B_Pin				14
#define batteryVoltageAdc_Pin	36

/*
#define SPI_SS_Pin				5		// Example SS (Slave Select) pin
#define SPI_RST_Pin				16		// Example Reset pin
#define SPI_DI0_Pin				2		// Example DIO0 pin
#define SPI_SCK_Pin				18		// Example SCK pin (Clock)
#define SPI_MISO_Pin			19		// Example MISO pin (Master In Slave Out)
#define SPI_MOSI_Pin			23		// Example MOSI pin (Master Out Slave In)
*/

#define BOARD_S2_RAW
//#define BOARD_V1

#ifdef BOARD_S2_RAW
  #define SPI_SS_Pin				38		// Example SS (Slave Select) pin
  #define SPI_RST_Pin				40		// Example Reset pin
  #define SPI_DI0_Pin				10		// Example DIO0 pin
  #define SPI_SCK_Pin				36		// Example SCK pin (Clock)
  #define SPI_MISO_Pin			21		// Example MISO pin (Master In Slave Out)
  #define SPI_MOSI_Pin			34		// Example MOSI pin (Master Out Slave In)

#elif defined(BOARD_V1)
  #define SPI_SS_Pin				34		// Example SS (Slave Select) pin
  #define SPI_RST_Pin				21		// Example Reset pin
  #define SPI_DI0_Pin				10		// Example DIO0 pin
  #define SPI_SCK_Pin				36		// Example SCK pin (Clock)
  #define SPI_MISO_Pin			40		// Example MISO pin (Master In Slave Out)
  #define SPI_MOSI_Pin			38		// Example MOSI pin (Master Out Slave In)

  #define touchButtonLeft_Pin   13
  #define touchButtonLeft_Pin   14

#else
    #error "No board defined. Please define a board (e.g., BOARD_A or BOARD_B)."
#endif

//define channels
#define vibrationMotor_Channel	2
#define WS2812B_Channel			3
#define ledStrip_Channel		4
#define ignition_Channel		5

//debug
#define testLED 15
#define testButton 0