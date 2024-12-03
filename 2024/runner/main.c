/*
	 TODO:
	 - read up on all the port config logic, don't want to just use random
	   code without understanding how it works
*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <termios.h>

int open_serial_port(const char * device, uint32_t baud_rate)
{
	int fd = open(device, O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (fd == -1)
	{
		perror(device);
		return -1;
	}

	// Flush away any bytes previously read or written.
	int result = tcflush(fd, TCIOFLUSH);
	if (result)
	{
		perror("tcflush failed");  // just a warning, not a fatal error
	}

	// Get the current configuration of the serial port.
	struct termios options;
	result = tcgetattr(fd, &options);
	if (result)
	{
		perror("tcgetattr failed");
		close(fd);
		return -1;
	}

	// Turn off any options that might interfere with our ability to send and
	// receive raw binary bytes.
	options.c_iflag &= ~(INLCR | IGNCR | ICRNL | IXON | IXOFF);
	options.c_oflag &= ~(ONLCR | OCRNL);
	options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	options.c_cflag |= (CLOCAL | CREAD); // Ignore modem control lines, enable receiver
	options.c_cflag &= ~CRTSCTS;        // Disable hardware flow control
	options.c_iflag &= ~(IXON | IXOFF | IXANY); // Disable software flow control

	// Set up timeouts: Calls to read() will return as soon as there is
	// at least one byte available or when 100 ms has passed.
	options.c_cc[VTIME] = 100;
	options.c_cc[VMIN] = 0;

	// This code only supports certain standard baud rates. Supporting
	// non-standard baud rates should be possible but takes more work.
	switch (baud_rate)
	{
		case 4800:
			cfsetospeed(&options, B4800);
			break;
		case 9600:
			cfsetospeed(&options, B9600);
			break;
		case 19200:
			cfsetospeed(&options, B19200);
			break;
		case 38400:
			cfsetospeed(&options, B38400);
			break;
		case 115200:
			cfsetospeed(&options, B115200);
			break;
		default:
			fprintf(stderr, "warning: baud rate %u is not supported, using 9600.\n", baud_rate);
			cfsetospeed(&options, B9600);
			break;
	}
	cfsetispeed(&options, cfgetospeed(&options));

	result = tcsetattr(fd, TCSANOW, &options);
	if (result)
	{
		perror("tcsetattr failed");
		close(fd);
		return -1;
	}

	return fd;
}

int write_port(int fd, uint8_t * buffer, size_t size)
{
	ssize_t result = write(fd, buffer, size);
	if (result != (ssize_t)size)
	{
		perror("failed to write to port");
		return -1;
	}
	return 0;
}
ssize_t read_port(int fd, uint8_t * buffer, size_t size)
{
	size_t received = 0;
	while (received < size)
	{
		ssize_t r = read(fd, buffer + received, size - received);
		if (r < 0)
		{
			perror("failed to read from port");
			return -1;
		}
		if (r == 0)
		{
			printf("timeout\n");
			break;
		}
		received += r;
	}
	return received;
}

int main(void)
{
	printf("running...\n");
	const char* device = "/dev/tty.usbmodem21401";
	uint32_t baud_rate = 115200;

	int fd = open_serial_port(device, baud_rate);
	if (fd < 0) { return 1; }
	
	uint8_t start = '1';
	write_port(fd, &start, 1);

	uint8_t started[10];
	ssize_t bytes_read = read_port(fd, started, 10);
	printf("read %zd bytes\n", bytes_read);
	for (ssize_t i = 0; i < bytes_read; i++) {
		printf("Byte %zd: 0x%02X ('%c')\n", i, started[i], started[i]);
	}
}

