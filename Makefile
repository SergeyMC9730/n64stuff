ROMNAME = release

CFLAGS += -I/usr/include/libdragon

all: $(ROMNAME).z64
.PHONY: all

BUILD_DIR = build
include $(N64_INST)/include/n64.mk

OBJS = $(BUILD_DIR)/main.o

$(ROMNAME).z64: N64_ROM_TITLE = "$(ROMNAME)"

$(BUILD_DIR)/$(ROMNAME).elf: $(OBJS)

clean:
	rm -rf $(BUILD_DIR) *.z64
.PHONY: clean

-include $(wildcard $(BUILD_DIR)/*.d)

buildrom:
	libdragon make