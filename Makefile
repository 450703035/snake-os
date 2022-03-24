ARMGNU ?= aarch64-elf

board ?= rpi4

ifeq ($(board), rpi3)
COPS += -DCONFIG_BOARD_PI3B
QEMU_FLAGS  += -machine raspi3
else ifeq ($(board), rpi4)
COPS += -DCONFIG_BOARD_PI4B
QEMU_FLAGS  += -machine raspi4
endif

CPU = Cortex-A72
ARCH = armv8-a
TARGET_CPU = -mcpu=$(CPU)
TARGET_ARCH = -march=$(ARCH) $(TARGET_CPU) 

COPS += -g -Wall -nostdlib -Iinclude -mgeneral-regs-only -ffreestanding -nostartfiles
ASMOPS = -g -Iinclude 

LDFLAGS = -Map snake-os.map -T $(SRC_DIR)/linker.ld

BUILD_DIR = build
SRC_DIR = src

$(BUILD_DIR):
	mkdir $@


all : snake-os.bin

clean :
	rm -rf $(BUILD_DIR) *.bin *.elf *.map 

$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(ARMGNU)-gcc $(TARGET_ARCH) $(COPS) -MMD -c $< -o $@

$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.S | $(BUILD_DIR)
	$(ARMGNU)-gcc $(TARGET_ARCH) $(ASMOPS) -MMD -c $< -o $@

C_FILES = $(wildcard $(SRC_DIR)/*.c)
ASM_FILES = $(wildcard $(SRC_DIR)/*.S)
OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%_s.o)

DEP_FILES = $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)

snake-os.bin: $(SRC_DIR)/linker.ld $(OBJ_FILES)
	$(ARMGNU)-ld  $(LDFLAGS)  -o snake-os.elf  $(OBJ_FILES)
	$(ARMGNU)-objcopy snake-os.elf -O binary snake-os.bin

QEMU_FLAGS  += -nographic

run:
	qemu-system-aarch64 $(QEMU_FLAGS) -kernel snake-os.bin
debug:
	qemu-system-aarch64 $(QEMU_FLAGS) -kernel snake-os.bin -S -s
