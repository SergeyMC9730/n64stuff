ROMNAME = release

CFLAGS += -I/usr/include/libdragon

all: $(ROMNAME).z64
.PHONY: all

BUILD_DIR = build
include $(N64_INST)/include/n64.mk

OBJS = $(wildcard src/*.c)

$(ROMNAME).z64: N64_ROM_TITLE = "$(ROMNAME)"
$(ROMNAME).z64: $(BUILD_DIR)/$(ROMNAME).dfs

$(BUILD_DIR)/$(ROMNAME).dfs: $(wildcard filesystem/*)
$(BUILD_DIR)/$(ROMNAME).elf: $(OBJS)

clean:
	rm -rf $(BUILD_DIR) *.z64
.PHONY: clean

-include $(wildcard $(BUILD_DIR)/*.d)

buildrom:
	libdragon make