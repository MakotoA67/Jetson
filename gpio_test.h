#ifndef __GPIO_TEST_H__
#define __GPIO_TEST_H__

#define		TEST_FOR_JETSON_ORIN_NANO	// for Jetson Orin Nano
//#define		TEST_FOR_JETSON_XAVIER_NX	// for Jetson Xavier NX
//#define		TEST_FOR_JETSON_TX2_NX	// for Jetson TX2 NX
// no define // for Jetson Nano

#if defined(TEST_FOR_JETSON_ORIN_NANO)
// Jetson Orin Nano

// GPIO_398  // Jetson Orin Nano Pin12 PH.07 input
// GPIO_454  // Jetson Orin Nano Pin31 PQ.06 output
// GPIO_399  // Jetson Orin Nano Pin40 PI.00 input

#define	GPIO_INPUT_LINE_OFFSET		(50)	// Pin12
#define	GPIO_OUTPUT_LINE_OFFSET		(106)	// Pin31
#define	GPIO_OUTPUT_LINE_OFFSET_2	(51)	// Pin40

#elif defined(TEST_FOR_JETSON_XAVIER_NX)
// Jetson Xavier NX

// GPIO_445  0x022138a0    // Jetson Xavier NX Pin12 T.05 input
// GPIO_422  0x02212cc0    // Jetson Xavier NX Pin31 Q.06 output

#define	GPIO_INPUT_LINE_OFFSET		(445 - 288)	// Pin12
#define	GPIO_OUTPUT_LINE_OFFSET		(422 - 288)	// Pin31
#define	GPIO_OUTPUT_LINE_OFFSET_2	(446 - 288)	// Pin40

#elif defined(TEST_FOR_JETSON_TX2_NX)
// Jetson TX2 NX

// GPIO_392  Jetson TX2 NX Pin12 J.00 input
// GPIO_394  Jetson TX2 NX Pin38 J.02 output

#define	GPIO_INPUT_LINE_OFFSET		(72)	// Pin12
#define	GPIO_OUTPUT_LINE_OFFSET		(242 - 192)	// Pin31 (gpiochip1)
#define	GPIO_OUTPUT_LINE_OFFSET_2	(73)	// Pin40

#else
// Jetson Nano

// GPIO_79   0x6000d204    // Jetson Nano Pin12 J.07 input
// GPIO_200  0x6000d604    // Jetson Nano Pin31 Z.00 output

#define	GPIO_INPUT_LINE_OFFSET		79	// Pin12
#define	GPIO_OUTPUT_LINE_OFFSET		200	// Pin31
#define	GPIO_OUTPUT_LINE_OFFSET_2	78	// Pin40

#endif /* TEST_FOR_JETSON_XAVIER_NX */

#endif /* __GPIO_TEST_H__ */

