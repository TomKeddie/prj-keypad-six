OUTPUT_DIR=output
BUILD_DIR=build
BUS_PIRATE_PORT=/dev/ttyUSB1
FQBN=arduino:avr:leonardo

all : $(OUTPUT_DIR)/keypad-six-test.ino.hex

$(OUTPUT_DIR)/keypad-six-test.ino.hex : keypad-six-test.ino ../keypad-six.h
	arduino-cli --verbose --log-file compile.cli.log --log-format text --log-level trace compile --library ".." --build-path build --output-dir $(OUTPUT_DIR) --output-dir $(OUTPUT_DIR) --warnings all --fqbn $(FQBN) keypad-six-test

prog : $(OUTPUT_DIR)/keypad-six-test.ino.hex
	arduino-cli --verbose upload --input-dir $(OUTPUT_DIR) --fqbn $(FQBN) --programmer buspirate --protocol serial --port $(BUS_PIRATE_PORT) keypad-six-test

bootloader:
	arduino-cli --verbose burn-bootloader --fqbn $(FQBN) --programmer buspirate --protocol serial --port $(BUS_PIRATE_PORT)

clean :
	rm -rf $(OUTPUT_DIR)
	rm -rf $(BUILD_DIR)
