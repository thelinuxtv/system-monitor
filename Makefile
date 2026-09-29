CC = gcc
CFLAG = -Wall -Wextra -O2
TARGET = system-monitor
SRC = src/main.c \
      src/monitor.c

OBJ = $(SRC:.c=.o)

all: $(TARGET)
	sudo apt update
	sudo apt upgrade
	sudo apt install vim build-essential binutils
	sudo cp ./system-monitor /usr/local/bin
	sudo cp ./system-monitor ./bin
	sudo cp ./systemd/system-monitor.service /etc/systemd/system
	sudo systemctl daemon-reload 
	sudo systemctl enable --now system-monitor



$(TARGET): $(OBJ)
	$(CC) $(CFLAG) $(OBJ) -o $(TARGET)


%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

start:
	sudo systemctl start system-monitor.service

stop:
	sudo systemctl stop system-monitor.service

status:
	sudo systemctl status system-monitor.service

clean: 
	rm -rf $(OBJ) $(TARGET) bin/system-monitor
