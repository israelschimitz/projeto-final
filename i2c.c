#include <stdio.h>
#include <unistd.h>
#include <string.h>

FILE *sensor;

void main (int argc, char **argv) 
{
	int leitura;
	char valor[20];
	
	sensor= fopen ("/sys/bus/i2c/devices/0-0050/eeprom","r");
	fscanf (sensor, "%s", valor);
	fclose(sensor);
	leitura= atoi (valor);

	printf("valor: %d\n",leitura);
	return (leitura);


}


