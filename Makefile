TARGET = mono_project
ARCH="/usr/local/gcc-arm-none-eabi-4_8/bin/arm-none-eabi-"
FLASH_SIZE=262144
FLASH_ROW_SIZE=256
FLASH_ARRAY_SIZE=65536
EE_ARRAY=64
EE_ROW_SIZE=16
OPTIMIZATION = -O0
CYPRESS_DIR=Generated_Source/PSoC5
LINKER_SCRIPT=${CYPRESS_DIR}/cm3gcc.ld
BUILD_DIR=build
COMP_LIB="lib/CyComponentLibrary.a"
MONO_CY_LIB=build/monoCyLib.a
MBED_PATH=../mbedcomp
MONO_FW_PATH=../mono_framework

OBJECTS =	$(patsubst %.c,%.o,$(wildcard *.c)) $(patsubst %.cpp,%.o,$(wildcard *.cpp))

MBED_OBJECTS =	$(patsubst %.c,%.o,$(wildcard $(MBED_PATH)/*.c)) \
				$(patsubst %.cpp,%.o,$(wildcard $(MBED_PATH)/*.cpp))

MONO_OBJECTS = 	$(patsubst %.cpp,%.o,$(wildcard $(MONO_FW_PATH)/*.cpp)) \
				$(patsubst %.cpp,%.o,$(wildcard $(MONO_FW_PATH)/display/*.cpp)) \
				$(patsubst %.cpp,%.o,$(wildcard $(MONO_FW_PATH)/display/ui/*.cpp)) \
				$(patsubst %.cpp,%.o,$(wildcard $(MONO_FW_PATH)/display/hx8340/*.cpp)) \
				$(patsubst %.cpp,%.o,$(wildcard $(MONO_FW_PATH)/wireless/*.cpp)) 

SYS_OBJECTS = 	$(patsubst %.c,%.o,$(wildcard Generated_Source/PSoC5/*.c)) \
				$(patsubst %.s,%.o,$(wildcard Generated_Source/PSoC5/*Gnu.s))

CC=$(ARCH)gcc
CXX=$(ARCH)g++
LD=$(ARCH)gcc
AS=$(ARCH)gcc
AR=$(ARCH)ar
RANLIB=$(ARCH)ranlib
STRIP=$(ARCH)strip
OBJCOPY=$(ARCH)objcopy
OBJDUMP=$(ARCH)objdump
COPY=cp
MKDIR=mkdir
ELFTOOL='C:\Program Files (x86)\Cypress\PSoC Creator\3.1\PSoC Creator\bin\cyelftool.exe'
INCS =	-I . \
	 	-I ${CYPRESS_DIR} \
		-I $(MBED_PATH) \
		-I $(MONO_FW_PATH) \
		-I $(MONO_FW_PATH)/display \
		-I $(MONO_FW_PATH)/display/ui \
		-I $(MONO_FW_PATH)/display/hx8340 \
		-I $(MONO_FW_PATH)/wireless
CDEFS=
ASDEFS=
AS_FLAGS = -c -g -Wall -mcpu=cortex-m3 -mthumb -mthumb-interwork -march=armv7-m
CC_FLAGS = -c -g -Wall -mcpu=cortex-m3 -mthumb $(OPTIMIZATION) -mthumb-interwork -fno-common -fmessage-length=0 -ffunction-sections -fdata-sections -march=armv7-m
ONLY_C_FLAGS = -std=gnu99 
ONLY_CPP_FLAGS = -std=gnu++98 -fno-rtti -fno-exceptions
LDSCRIPT = -T ${LINKER_SCRIPT}
LD_FLAGS = -g -mcpu=cortex-m3 -mthumb -march=armv7-m -fno-rtti -Wl,--gc-sections -specs=nano.specs 
LD_SYS_LIBS = -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys

#"libs/CyCompLib.a"
#   -mfix-cortex-m3-ldrd -u _printf_float -u _scanf_float
COPY_FLAGS = -j .text -j .eh_frame -j .rodata -j .ramvectors -j .noinit -j .data -j .bss -j .stack -j .heap -j .cyloadablemeta

all: $(BUILD_DIR) $(TARGET).elf

library: monoCyLib.a

$(BUILD_DIR):
	@echo "creating build directory"
	@mkdir -p ./$(BUILD_DIR)

.s.o: $(BUILD_DIR)
	@echo "Assembling: $(notdir $<)"
	@$(AS) $(AS_FLAGS) $(INCS) -o $(BUILD_DIR)/$(notdir $@) $<

.c.o: $(BUILD_DIR)
	@echo "Compiling C: $(notdir $<)"
	@$(CC) $(CC_FLAGS) $(ONLY_C_FLAGS) $(CDEFS) $(INCS) -o $(BUILD_DIR)/$(notdir $@) $<

.cpp.o: $(BUILD_DIR)
	@echo "Compiling C++: $(notdir $<)"
	@$(CXX) $(CC_FLAGS) $(ONLY_CPP_FLAGS) $(CDEFS) $(INCS) -o $(BUILD_DIR)/$(notdir $@) $<

$(TARGET).elf: $(OBJECTS) $(MBED_OBJECTS) $(MONO_OBJECTS)
	@echo "Linking $(notdir $@)"
	@$(LD) -Wl,--start-group -o $@ $(addprefix $(BUILD_DIR)/, $(notdir $^)) $(MONO_CY_LIB) -mthumb -march=armv7-m -mfix-cortex-m3-ldrd "-Wl,-Map,mono_project.map" -T $(LINKER_SCRIPT) -g -specs=nano.specs "-u\ _printf_float" $(LD_SYS_LIBS) -Wl,--gc-sections -Wl,--end-group

$(TARGET).hex: $(TARGET).elf
	$(ELFTOOL) -C $^ --flash_size $(FLASH_SIZE) --flash_row_size $(FLASH_ROW_SIZE)
	$(OBJCOPY) -O ihex $(COPY_FLAGS) $< $@
	$(ELFTOOL) -B $^ --flash_size $(FLASH_SIZE) --flash_array_size $(FLASH_ARRAY_SIZE) --flash_row_size $(FLASH_ROW_SIZE) --ee_array $(EE_ARRAY) --ee_row_size $(EE_ROW_SIZE)

$(TARGET):  $(OBJS)  ${LINKER_SCRIPT}
	@echo "Other link: $(OBJS)"
	$(LD) $(LDSCRIPT) $(OBJS) -o $@

monoCyLib.a: $(SYS_OBJECTS)
	@echo "Linking static library"
	@$(AR) rcs lib/$@ $(addprefix $(BUILD_DIR)/, $(notdir $^)) $(COMP_LIB)
	@$(COPY) lib/$@ $(BUILD_DIR)/$@
	@echo "Copying header files to include dir"
	@$(MKDIR) -p include
	@$(COPY) $(CYPRESS_DIR)/*.h include/

systemFiles:
	@echo $(SYS_OBJECTS)
	
appFiles:
	@echo $(OBJECTS)
	
mbedFiles:
	@echo $(MBED_OBJECTS)
	
monoFiles:
	@echo $(MONO_OBJECTS)

clean:
	$(RM) $(addprefix $(BUILD_DIR)/, $(notdir $(OBJECTS))) $(addprefix $(BUILD_DIR)/, $(notdir $(SYS_OBJECTS))) $(TARGET).elf $(TARGET).bin include/* lib/monoCyLib.a

summary: $(TARGET).elf
	$(ELFTOOL) -S $(TARGET).elf
	

## $(LD) -Wl,--start-group $(LD_FLAGS) libs/CyCompLib.a $(LDSCRIPT) -o $@ $^ -Wl,--end-group $(LD_SYS_LIBS)
## $(ELFTOOL) -C $@ --flash_size $(FLASH_SIZE) --flash_row_size $(FLASH_ROW_SIZE)