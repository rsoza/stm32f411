Step1: New project
	- create a STM32 project with the appropriate part number
	- nucleo-stm32f411re
	- click next, bottom right
	- give project name, select empty project name
	- expand src >> main.c erase contents
	
	OBJECTIVE: Turn on LED
				Q: Where is the led connected?
					A: start by looking for port and pin
				
				- To find port and pin go to USER GUIDE under LED section in contents
				- 2 types of LED: LD3 PWR (connect power), User LD2 (provides LED we can program) 
				- User LD2:: give port A pin 5

Step2: How to get to PA5 location bus and peripherals
	- go to datasheet
	- look for memory map section
		> this diagram shows the memory seperation of the microcontrollers
		> interested in peripherals block
		> peripherals starts from 0x4000 0000 - 0xFFFF FFFF
	- table gives more information on the memory map
		> table has three columns: bus, boundary adress, peripheral
		> which bus to choose? 
			- search for block diagram
			- shows the buses
			- there are two buses in this one: Advance Peripheral Bus (APB1 AND APB2) 6 clock cycles
			- two other one AHB 2 clock cycles
			- we want to know where GPIO port A is getting its supply?
				AHB1 supplies GPIOA
			- once bus is chosen go back to memory mapping
		> why have buses?
			every peripheral or module needs access to the clock which is through the bus
			***buses transporters of clock to the various peripherals
		> back in memory map table:
			- look for GPIOA in AHB1 
			- starting address is 0x4002 meaning there is a offset of 0x0002 0000 from peripheral base
			- this is the starting point == GPIOA starting point == address == AHB1 peripheral
		> another module aside from AHB1: RCC
			***enables each bus to transports a clock
			- Resetting clock control
			- look for address and offset it from base address from GPIOA
		> GPIOA and RCC are houses that need rooms to interact with called REGISTERS

Step3: Locate the registers
	- go to reference manual
	- search for bus (AHB1EN - AHB1 enable)
	- shows this is a 32 bit registers
	- has an offset, when you add it to the RCC base address you will arrive to AHB1EN
	- bit 0 has GPIOA: there is an explanation for setting 0 or 1
		> to set the bit to 0 or 1: (1U<<0) 
			1u = bit setting and 0 is the position of register
	- search for moder = MODE REGISTER in reference manual
		> this address is for all GPIOx
		> the offset plus GPIOA base gives you the right location
		> mode_R is in 2 byte with 16 moder
		> this sets the pin to output or input (0/1 bit)
		> use the output register in GPIO port output data register to out an led
	- all registers need to be set to volatile unsigned int pointer type casted/dereferenced
	
	
	
			AND operation: &=~
			
			
	
	
	