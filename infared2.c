#define F_CPU 3686400UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#define BAUD 115200
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)

// this is on davids laptop *************************************************************************

void USART_Init(){
	UBRRH = (unsigned char)(BAUDRATE >> 8);
	UBRRL = (unsigned char)(BAUDRATE);
	UCSRB = (1 << TXEN ) | (1 << RXEN); 

}

void USART_Transmit(unsigned char data){
	while(!(UCSRA & (1 << UDRE)));
	UDR = data;
}

uint8_t USART_Recieve(void) {
	while (!(UCSRA & (1 << RXC)))
	;
	return UDR;
}

void TWI_Init(void){

	TWSR = 0x00;
	TWBR = 0x01;
	TWCR = (1 << TWEN);

}

void TWIStart(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
}
//send stop signal
void TWIStop(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}


void TWIWrite(uint8_t u8data){

	TWDR = u8data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (( TWCR & (1<<TWINT)) ==0);
}

uint8_t TWIReadACK(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}

//read byte then send NACK
uint8_t TWIReadNACK(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}

uint8_t TWIGetStatus(void)
{
	uint8_t status;
	//mask status
	status = TWSR & 0xF8;
	return status;
}

uint8_t StartInfraredSensor(uint8_t address) {
	
	TWIStart(); // 
	
	TWIWrite(address);
	
	TWIWrite(0x00);
	
	TWIWrite(0x18); // 

	TWIWrite(0x03);

	TWIStop();
}

uint8_t ReadDistance(uint8_t address){
	uint8_t distance;

	TWIStart();
	
	DDRD |= (1 << DDD7); // turns on led output

	TWIWrite(address);

	TWIWrite(0x00);        

	TWIWrite(0x4F);

	
	//address |= 0x01;

	TWIWrite(0x53);

	distance = TWIReadNACK();

	TWIWrite(address);

	TWIWrite(0x00);        

	TWIWrite(0x62);

	
	//address |= 0x01;

	TWIWrite(0x53);

	distance = TWIReadNACK();

	TWIWrite(address);
	
	TWIWrite(0x00);        

	TWIWrite(0x15);

	TWIWrite(0x01);

	//TWIStop();	

	return distance; 

}


int main(void) {
	uint8_t distance;
	uint16_t message = 0x1a2b;
	uint8_t address = 0x52;
	
	USART_Init();

	TWI_Init();	

	StartInfraredSensor(address);

	while(1){
		
		USART_Transmit(message >> 8);
		USART_Transmit(message);
		USART_Transmit(distance);		
		
		distance = ReadDistance(address);
		
		PORTD ^= (1<<PD7);
		_delay_ms(500);


	}

	

		

}
