PASS = \033[0;32m
WARN = \033[0;31m
DEBUG = \033[0;33m
END = \033[0m

AR_CLI = arduino-cli
board_list := ${shell arduino-cli board list}

#
# To get information of the board. Please running arduino-cli board list
# And make sure you board is securely connect
#
FQBN_BOARD = arduino:renesas_uno:unor4wifi # TODO: Enter the FQBN of the board
PORT = /dev/ttyACM0 # TODO: Enter the port that's connect to the board
SERIAL = 9600

#
# TODO: always run with sketch name specify in variable
# example:
# >~ make NAME=${YOUR_SKETCH_NAME}
#
NAME :=

COMPILE_FLAGS = -b

all: upload

compile: check ${NAME}
	${AR_CLI} compile ${COMPILE_FLAGS} ${FQBN_BOARD} ${NAME}

upload: compile ${NAME}
	${AR_CLI} upload -p ${PORT} -b ${FQBN_BOARD} ${NAME}

new:
	@ if [ -z "$(NAME)" ]; then \
		echo -e "${WARN}Please enter the name of sketch.${END}"; \
		exit 1;\
	fi
	@${AR_CLI} sketch new ${NAME}

check:
	@ echo -e "${DEBUG}Checking is there any board connected...${END}"
	@ if [ ${shell arduino-cli board list | wc -l} -lt 3 ]; then \
		echo -e "${WARN}No Board Connected, Please check your board or cable.${END}"; \
		exit 1; \
	else \
		echo -e "${PASS}Board connected.${END}"; \
	fi
	@ echo -e "${DEBUG}Checking FQBN...${END}"
	@ if [ -z "$(FQBN_BOARD)" ]; then \
		echo -e "${WARN}No FQBN suplies to the variable make sure to enter it in the Makefile.${END}"; \
		exit 1; \
	elif [[ "${board_list}" =~ "${FQBN_BOARD}" ]]; then \
		echo -e "${PASS}FQBN match in board list.${END}"; \
	else \
		echo -e "${WARN}FQBN not match any board you connect.${END}"; \
		exit 1; \
	fi
	@ echo -e "${DEBUG}Checking port...${END}"
	@ if [ -z "$(PORT)" ]; then \
		echo -e "${WARN}Port unspecified in the variable make sure to enter it in the Makefile.${END}"; \
		exit 1; \
	elif [[ "${board_list}" =~ "${PORT}" ]]; then \
		echo -e "${PASS}Port match in board list.${END}"; \
	else \
		echo -e "${WARN}Port not match any board you connect.${END}"; \
		exit 1; \
	fi
	@ if [ -z "$(NAME)" ]; then \
		echo -e "${WARN}Please enter the name of sketch.${END}"; \
		exit 1;\
	elif [ ! -d ${NAME} ]; then \
		echo -e "${WARN}${NAME} sketch doesn't exist.${END}"; \
	fi

list:
	@echo "${board_list}"

monitor: 
	${AR_CLI} monitor -p ${PORT} --config ${SERIAL}

.PHONY: all compile upload new check list
