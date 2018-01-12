CC	:= avr-gcc
TARGET1 := infared2
TARGET3 := current_sensor
TARGET4 := atmega_wifi
TARGET5 := custom_wifi
SREXT   := .c
OBJEXT  := .o
ELFEXT  := .elf
HEXEXT  := .hex
UC      := atmega8

$(TARGET1):
	$(CC) -g -Os -mmcu=$(UC) -c $(TARGET1)$(SREXT)
	$(CC) -g -mmcu=$(UC) -o $(TARGET1)$(ELFEXT) $(TARGET1)$(OBJEXT)
	avr-objcopy -j .text -j .data -O ihex $(TARGET1)$(ELFEXT) $(TARGET1)$(HEXEXT)

$(TARGET2):
	$(CC) -g -Os -mmcu=$(UC) -c $(TARGET2)$(SREXT)
	$(CC) -g -mmcu=$(UC) -o $(TARGET2)$(ELFEXT) $(TARGET2)$(OBJEXT)
	avr-objcopy -j .text -j .data -O ihex $(TARGET2)$(ELFEXT) $(TARGET2)$(HEXEXT)

$(TARGET3):
	$(CC) -g -Os -mmcu=$(UC) -c $(TARGET3)$(SREXT)
	$(CC) -g -mmcu=$(UC) -o $(TARGET3)$(ELFEXT) $(TARGET3)$(OBJEXT)
	avr-objcopy -j .text -j .data -O ihex $(TARGET3)$(ELFEXT) $(TARGET3)$(HEXEXT)

$(TARGET4):
	$(CC) -g -Os -mmcu=$(UC) -c $(TARGET4)$(SREXT)
	$(CC) -g -mmcu=$(UC) -o $(TARGET4)$(ELFEXT) $(TARGET4)$(OBJEXT)
	avr-objcopy -j .text -j .data -O ihex $(TARGET4)$(ELFEXT) $(TARGET4)$(HEXEXT)


$(TARGET5):
	$(CC) -g -Os -mmcu=$(UC) -c $(TARGET5)$(SREXT)
	$(CC) -g -mmcu=$(UC) -o $(TARGET5)$(ELFEXT) $(TARGET5)$(OBJEXT)
	avr-objcopy -j .text -j .data -O ihex $(TARGET5)$(ELFEXT) $(TARGET5)$(HEXEXT)


clean:
	$(RM) *.hex *.o *.elf
