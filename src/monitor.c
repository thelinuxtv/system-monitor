#include <stdio.h>
#include <string.h>

#include "../include/monitor.h"

void print_uptime(void) {
	FILE *file;
	double uptime;

	file = fopen("/proc/uptime", "r");
	if (file  == NULL) {
		perror("fopen /proc/uptime");
		return;
	}

	if (fscanf(file, "%lf", &uptime) != 1) {
		fprintf(stderr, "Failed to read uptime\n");
		fclose(file);
		return;
	}

	fclose(file);

	printf("Uptime: %.2f seconds\n", uptime);
}


void print_memory(void) {
	FILE *file;
	char line[256];

	file = fopen("/proc/meminfo", "r");
	if (file == NULL) {
		perror("fopen /proc/meminfo");
		return;
	}

	while (fgets(line, sizeof(line), file)) {
		if (strncmp(line, "MemTotal:", 9) == 0 || strncmp(line, "MemAvailable:", 13) == 0) {
			printf("%s", line);
		}
	}

	fclose(file);
}


void print_load(void) {
	FILE *file;
	double load1;
	double load5;
	double load15;

	file = fopen("/proc/loadavg", "r");
	if (file == NULL) {
		perror("fopen /proc/loadavg");
		return;
	}

	if (fscanf(file, "%lf %lf %lf", &load1, &load5, &load15) != 3) {
		fprintf(stderr, "Failed to read load average\n");
		fclose(file);
		return;
	}

	fclose(file);

	printf("Load average: %.2f\t%.2f\t%.2f\n", load1, load5, load15);
	
}
