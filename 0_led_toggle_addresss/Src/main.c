#define PERIPH_BASE			(0x40000000UL) // 4000 0000
#define AHB1PERIPH_OFFSET	(0x00020000UL) // 0002 0000

//starting point
#define AHB1PERIPH_BASE		(PERIPH_BASE + AHB1PERIPH_OFFSET) // 4002 0000

#define GPIOA_OFFSET		(0x0000UL) // hex =32 bit values, doesn't matter if it is 4 or 8 digits
#define GPIOA_BASE			(AHB1PERIPH_BASE + GPIOA_OFFSET) // 4002 0000

#define RCC_OFFSET			(0x3800UL) // this equals 0x0000 38000
#define RCC_BASE			(AHB1PERIPH_BASE + RCC_OFFSET) // 4002 3800

//r = register
#define AHB1EN_R_OFFSET		(0x30UL)
#define RCC_AHB1EN_R		(*(volatile unsigned int *) (RCC_BASE + AHB1EN_R_OFFSET))

#define MODE_R_OFFSET		(0x00UL)
#define GPIOA_MODE_R		(*(volatile unsigned int *) (GPIOA_BASE + MODE_R_OFFSET))

#define OD_R_OFFSET			(0x14UL)
#define GPIOA_OD_R			(*(volatile unsigned int *) (GPIOA_BASE + OD_R_OFFSET))  // 4002 1400 here we are interested in pin 5

#define GPIOAEN				(1U<<0)

// PIN5 set
#define PIN5				(1U<<5)
#define LED_PIN				PIN5



int main(void)
{
	// 1. Enable clock access to GPIOA
	// The OR operator will set only on bit to 1 called FRIENDLY programming
	RCC_AHB1EN_R |= GPIOAEN;

	// 2. Set PA5 as output pin
	GPIOA_MODE_R |= (1U<<10); // set bit 10 to 1
	GPIOA_MODE_R &=~ (1U<<11); // set bit 11 to 0


	while(1){
		// 3. Set PA5 high
		// friendly programming
//		GPIOA_OD_R |= LED_PIN;

		// 4. Experiment 2: toggle PA5 on/off
		// this is too fast for us to see
		GPIOA_OD_R ^= LED_PIN;
		// this makes the toggle happen every 100 000 seconds
		for (int i =0; i<100000;i++) {
		}
	}
}