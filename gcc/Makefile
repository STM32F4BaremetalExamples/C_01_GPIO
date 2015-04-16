INCLUDE_DIRS:= device/include cmsis/include ../include 
SOURCE_DIRS:=  device/source ../source

#the C files to compile
CFILES:= system_stm32f4xx.c main.c  
#the assembly files assemble
ASM_FILES:= startup_stm32f401xe.S
#the target microcontroller
TCHIP=STM32F401xx
#The compiler to use
CC=arm-none-eabi-gcc
#LINKER OPTIONS
#The linker script for the microcontroller 
LD_SCRIPTS:= stm32f401xe.ld
#the directories for linker files 
LIB_DIRS:= device/linker
#the libraries to link 
LIB_NAMES:=
#linker flags 
LFLAGS:= $(patsubst %,-L%,$(LIB_DIRS)) $(patsubst %,-l%,$(LIB_NAMES)) -T$(LD_SCRIPTS) 

INCLUDE_FLAGS:=$(patsubst %,-I%,$(INCLUDE_DIRS)) 
CFLAGS= -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=c99 -g -Wall
CPPFLAGS= $(INCLUDE_FLAGS) -D$(TCHIP)
vpath %.h $(INCLUDE_DIRS)
vpath %.c $(SOURCE_DIRS)
vpath %.S device/source
vpath %.o objects

COBJECTS:= $(patsubst %.c,%.o,$(CFILES)) 
ASMOBJECTS:= $(patsubst %.S,%.o,$(ASM_FILES))

all: salida.elf 
objects:
	mkdir objects
salida.elf: objects $(COBJECTS) $(ASMOBJECTS)
	$(CC) $(CFLAGS) objects/*.o $(LFLAGS) -o $@
$(COBJECTS): %.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o objects/$@
$(ASMOBJECTS): %.o: %.S
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o objects/$@
.PHONY:clean rebuild burn
clean:
	rm -f  *.elf
	rm -fr objects
rebuild: clean all
burn: salida.elf
	openocd -f board/st_nucleo_f401re.cfg -c"init" -c"reset" -c"sleep 300" -c"reset halt" -c"sleep 300" -c"flash write_image erase salida.elf 0x00 elf" -c"reset" -c"shutdown"
debug: salida.elf
	openocd -f board/st_nucleo_f401re.cfg &>/dev/null & 
	sleep 1 ;
	! echo "reset" | telnet localhost 4444 ;
	! echo "reset halt" | telnet localhost 4444 ;
	sleep 1 ;
	arm-none-eabi-gdb --tui --eval-command="target remote localhost:3333" salida.elf ;	
	! echo "reset" | telnet localhost 4444 ;
	sleep 1 ;
	! echo "shutdown" | telnet localhost 4444 ;
