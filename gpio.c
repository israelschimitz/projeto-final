#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TOLERANCIAPOSITIVA 5
#define TOLERANCIANEGATIVA -5

int main (int argc, char **argv)
{
	FILE *gpio;
	FILE *adc;
	FILE *html;
	FILE *txt;

	int LeituraAD;
	char valor[20];
	int i=0;
	float Erro=0;
	int Referencia;
	char aux[6];
	int c;
	char *svalue = NULL;
	int opterr = 0;
	
	char graus [4];
//	while ((c = getopt (argc, argv, "s:")) != -1)
 //       	switch (c)
 //          	{
 //      		     	case 's':
 //            			svalue = optarg;
//			Referencia = atoi (svalue);
 //            			break;
 //          		case '?':
 //       			if (optopt == 's')
 //              				fprintf (stderr, "opção -%c precisa de um valor entre 0 a 330°.\n", optopt);
 //            			else if (isprint (optopt))
 //              				fprintf (stderr, "opção invalida `-%c'.\n", optopt);
 //           			else
 //              				fprintf (stderr,"opção invalida `\\x%x'.\n", optopt);
 //            			return 1;
//           	default:
//             		abort ();
//           	}
//	}
	
	

///--------------seta em high o 161 pino 10 para VCC do potenciometro
        //exporta a gpio 161***** 3,3 v para o pot
        gpio=fopen("/sys/class/gpio/export","w");
        fputs ("161",gpio);
        fclose (gpio);

        //seta a direção como saída
        gpio=fopen("/sys/class/gpio/gpio161/direction","w");
        fputs ("out",gpio);
        fclose (gpio);

	//escreve 1 na porta
        gpio=fopen("/sys/class/gpio/gpio161/value","w");
        fputs ("1",gpio);
        fclose (gpio);
///-----------------------------------------------------------------

//--------------seta em high o 193 PINO 17 para ENABLE----------------------------
        //exporta a gpio 193
        gpio=fopen("/sys/class/gpio/export","w");
        fputs ("193",gpio);
        fclose (gpio);

        //seta a direção como saída
        gpio=fopen("/sys/class/gpio/gpio193/direction","w");
        fputs ("out",gpio);
        fclose (gpio);


       //zera o Enable
         gpio=fopen("/sys/class/gpio/gpio193/value","w");
         fputs ("0",gpio);
         fclose (gpio);

///-----------------------------------------------------------------

//--------------seta em high o 166 pino 15 para IN 2--------------------
        //exporta a gpio 166
        gpio=fopen("/sys/class/gpio/export","w");
        fputs ("166",gpio);
        fclose (gpio);

        //seta a direção como saída
        gpio=fopen("/sys/class/gpio/gpio166/direction","w");
        fputs ("out",gpio);
        fclose (gpio);

        //escreve 1 na porta
      //  gpio=fopen("/sys/class/gpio/gpio166/value","w");
      //  fputs ("1",gpio);
      //  fclose (gpio);
///-----------------------------------------------------------------

//--------------seta em high o 165 pino 14 para IN 1----------------
        //exporta a gpio 165
        gpio=fopen("/sys/class/gpio/export","w");
        fputs ("165",gpio);
        fclose (gpio);

        //seta a direção como saída
        gpio=fopen("/sys/class/gpio/gpio165/direction","w");
        fputs ("out",gpio);
        fclose (gpio);

        //escreve 1 na porta
      //  gpio=fopen("/sys/class/gpio/gpio165/value","w");
      //  fputs ("1",gpio);
      //  fclose (gpio);
///-----------------------------------------------------------------

	printf("insira um angulo de 0 a 330°\n");
        gets(graus);
        Referencia = atoi (graus);
        if (Referencia > 330)
        	Referencia = 330;
        if (Referencia < 0)
                Referencia = 0;



	while (1)	
	{
	
			
		adc = fopen ("/sys/devices/platform/s3c24xx-adc/s3c-hwmon/in1_input", "r");
        	fscanf (adc, "%s", valor);
        	fclose (adc);
        	LeituraAD = atoi (valor);
        	LeituraAD = LeituraAD / 9.7;    //Converte de 0 a 3300 -> 0 a 330°
        	printf ("leitura = %d.\n", LeituraAD);
		usleep (100000);	
		
		Erro = Referencia - LeituraAD;

		if (Erro > 0) {

			//escreve 0 na porta ENABLE
                        gpio=fopen("/sys/class/gpio/gpio193/value","w");
                        fputs ("0",gpio);
                        fclose (gpio);
			usleep (100000);
			
		 	//escreve 0 na porta PIN 15 - IN2
	      		gpio=fopen("/sys/class/gpio/gpio166/value","w");
      			fputs ("0",gpio);
      			fclose (gpio); 
			
			//escreve 1 na porta PIN 14 - IN1
      			gpio=fopen("/sys/class/gpio/gpio165/value","w");
      			fputs ("1",gpio);
    			fclose (gpio);

			//escreve 1 na porta ENABLE
      			gpio=fopen("/sys/class/gpio/gpio193/value","w");
      			fputs ("1",gpio);
      			fclose (gpio);

		}
			
		if (Erro < 0) {
                       
			//escreve 0 na porta ENABLE
                        gpio=fopen("/sys/class/gpio/gpio193/value","w");
                        fputs ("0",gpio);
                        fclose (gpio);
                        usleep (100000);

			//escreve 1 na porta PIN 15 - IN2
                        gpio=fopen("/sys/class/gpio/gpio166/value","w");
                        fputs ("1",gpio);
                        fclose (gpio);

                        //escreve 0 na porta PIN 14 - IN1
                        gpio=fopen("/sys/class/gpio/gpio165/value","w");
                        fputs ("0",gpio);
                        fclose (gpio);

                        //escreve 1 na porta ENABLE
                        gpio=fopen("/sys/class/gpio/gpio193/value","w");
                        fputs ("1",gpio);
                        fclose (gpio);

                	}

		if ((Erro < TOLERANCIAPOSITIVA) && (Erro > TOLERANCIANEGATIVA))  {

		                       
                        //escreve 0 na porta ENABLE
                        gpio=fopen("/sys/class/gpio/gpio193/value","w");
                        fputs ("0",gpio);
                        fclose (gpio);

                        //escreve 0 na porta PIN 14 - IN1
                        gpio=fopen("/sys/class/gpio/gpio165/value","w");
                        fputs ("0",gpio);
                        fclose (gpio);

                        //escreve 0 na porta PIN 15 - IN2
                        gpio=fopen("/sys/class/gpio/gpio166/value","w");
                        fputs ("0",gpio);
                        fclose (gpio);
			// printf ("estou no filtro");
			
			break;

        	}
	
	
		txt= fopen("/var/www/index.html","w");
		sprintf (aux, "%d", LeituraAD);
		fputs("<html><head><META HTTP-EQUIV='REFRESH' CONTENT='1'></head><body>",txt);
		fputs("<h1> O eixo em graus eh: </h1>\n", txt);
		fputs(aux, txt);
		fputs("</body></html>",txt);
		
		fclose(txt);
	
	//	html = fopen("/var/www/index.html","w+");
	//		printf("content-type: text/html\n\n");
	//		printf("<html>\n<body>\n");
	//		printf("<h1> O eixo em graus é: </h1>\n");
	//		printf("<h1>       %d           </h1>\n", LeituraAD);
	//		printf("</body>\n</html>\n");
	//	fclose(html);
	}
	
	return 0;

}


