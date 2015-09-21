TARGET = mono_project
ARCH="/usr/local/gcc-arm-none-eabi-4_8/bin/arm-none-eabi-"
FLASH_SIZE=262144
FLASH_ROW_SIZE=256
FLASH_ARRAY_SIZE=65536
EE_ARRAY=64
EE_ROW_SIZE=16
OPTIMIZATION = -O0
INCLUDE_DIR=include
CYPRESS_DIR=Generated_Source/PSoC5
LINKER_SCRIPT=${INCLUDE_DIR}/cm3gcc.ld
BUILD_DIR=build
MONO_FRAMEWORK_PATH =../mono_framework
MBED_PATH=../mbedcomp
COMP_LIB=lib/CyComponentLibrary.a
MONO_LIB=lib/monoCyLib.a

OBJECTS =		$(patsubst %.c,%.o,$(wildcard *.c)) \
				$(patsubst %.cpp,%.o,$(wildcard *.cpp))

MBED_OBJECTS =	$(patsubst %.cpp,%.o,$(wildcard $(MBED_PATH)/*.cpp)) \
				$(patsubst %.c,%.o,$(wildcard $(MBED_PATH)/common/*.c)) \
				$(patsubst %.cpp,%.o,$(wildcard $(MBED_PATH)/common/*.cpp)) \
				$(patsubst %.c,%.o,$(wildcard $(MBED_PATH)/target_cypress/*.c))
				
MBED_INCLUDES =	$(MBED_PATH) \
				$(MBED_PATH)/api \
				$(MBED_PATH)/hal \
				$(MBED_PATH)/target_cypress

MONO_OBJECTS =	$(patsubst %.c,%.o,$(wildcard $(MONO_FRAMEWORK_PATH)/*.c)) \
				$(patsubst %.cpp,%.o,$(wildcard $(MONO_FRAMEWORK_PATH)/*.cpp)) \
				$(patsubst %.c,%.o,$(wildcard $(MONO_FRAMEWORK_PATH)/display/*.c)) \
				$(patsubst %.cpp,%.o,$(wildcard $(MONO_FRAMEWORK_PATH)/display/*.cpp)) \
				$(patsubst %.c,%.o,$(wildcard $(MONO_FRAMEWORK_PATH)/display/ui/*.c)) \
				$(patsubst %.cpp,%.o,$(wildcard $(MONO_FRAMEWORK_PATH)/display/ui/*.cpp)) \
				$(patsubst %.c,%.o,$(wildcard $(MONO_FRAMEWORK_PATH)/display/ili9225g/*.c)) \
				$(patsubst %.cpp,%.o,$(wildcard $(MONO_FRAMEWORK_PATH)/display/ili9225g/*.cpp)) \
				$(patsubst %.c,%.o,$(wildcard $(MONO_FRAMEWORK_PATH)/wireless/*.c)) \
				$(patsubst %.cpp,%.o,$(wildcard $(MONO_FRAMEWORK_PATH)/wireless/*.cpp)) \
				$(patsubst %.cpp,%.o,$(wildcard $(MONO_FRAMEWORK_PATH)/media/*.cpp))

MONO_INCLUDES =	$(MONO_FRAMEWORK_PATH) \
				$(MONO_FRAMEWORK_PATH)/display \
				$(MONO_FRAMEWORK_PATH)/display/ili9225g \
				$(MONO_FRAMEWORK_PATH)/display/ui \
				$(MONO_FRAMEWORK_PATH)/wireless \
				$(MONO_FRAMEWORK_PATH)/media

SYS_OBJECTS = 	$(patsubst %.c,%.o,$(wildcard $(CYPRESS_DIR)/*.c)) \
				$(patsubst %.s,%.o,$(wildcard $(CYPRESS_DIR)/*Gnu.s))

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
MONOPROG=monoprog
ELFTOOL='C:\Program Files (x86)\Cypress\PSoC Creator\3.1\PSoC Creator\bin\cyelftool.exe'
INCS = -I . -I ${CYPRESS_DIR} -I$(INCLUDE_DIR) $(addprefix -I, $(MBED_INCLUDES) $(MONO_INCLUDES))
CDEFS=
ASDEFS=
AS_FLAGS = -c -g -Wall -mcpu=cortex-m3 -mthumb -mthumb-interwork -march=armv7-m
CC_FLAGS = -c -g -Wall -mcpu=cortex-m3 -mthumb $(OPTIMIZATION) -mthumb-interwork -fno-common -fmessage-length=0 -ffunction-sections -fdata-sections -march=armv7-m
ONLY_C_FLAGS = -std=gnu99 
ONLY_CPP_FLAGS = -std=gnu++98 -fno-rtti -fno-exceptions
LDSCRIPT = -T $(LINKER_SCRIPT)
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
	@$(LD) -Wl,--start-group -o $@ $(addprefix $(BUILD_DIR)/, $(notdir $^)) $(MONO_LIB) -mthumb -march=armv7-m -mfix-cortex-m3-ldrd "-Wl,-Map,mono_project.map" -T $(LINKER_SCRIPT) -g -specs=nano.specs "-u\ _printf_float" $(LD_SYS_LIBS) -Wl,--gc-sections -Wl,--end-group

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
	@echo "Copying linker and header files to include dir"
	@$(MKDIR) -p include
	@$(COPY) $(CYPRESS_DIR)/*.h include/
	@$(COPY) $(CYPRESS_DIR)/cm3gcc.ld include/

monoLib.a: monoCyLib.a $(MBED_OBJECTS) $(MONO_OBJECTS)
	@echo "Linking Mono Framework"
	@$(AR) rcs lib/$@ $(addprefix $(BUILD_DIR)/, $(notdir $^)) $(COMP_LIB) $(MONO_LIB)

systemFiles:
	@echo $(SYS_OBJECTS)
	
appFiles:
	@echo $(OBJECTS)

mbedFiles:
	@echo $(MBED_OBJECTS)

monoFiles:
	@echo $(MONO_OBJECTS)

includeFiles: 
	@echo $(INCS)

install: $(TARGET).elf
	@echo "Programming app to device..."
	$(MONOPROG) -p $(TARGET).elf --verbose 1

clean:
	$(RM) $(addprefix $(BUILD_DIR)/, $(notdir $(OBJECTS))) $(addprefix $(BUILD_DIR)/, $(notdir $(SYS_OBJECTS))) $(TARGET).elf $(TARGET).bin

summary: $(TARGET).elf
	$(ELFTOOL) -S $(TARGET).elf
	

## $(LD) -Wl,--start-group $(LD_FLAGS) libs/CyCompLib.a $(LDSCRIPT) -o $@ $^ -Wl,--end-group $(LD_SYS_LIBS)
## $(ELFTOOL) -C $@ --flash_size $(FLASH_SIZE) --flash_row_size $(FLASH_ROW_SIZE)