#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
	int c,i,coma=0,columna,fila=1,conta=0;
	char nombre[100];
	printf("\n\tEscribe el nombre del archivo que deseas leer: ");
	scanf("%s",nombre);
	FILE *archivo = fopen(nombre,"rb");
	char *token;
	char linea[100];
	if(archivo == NULL)	
	{
		printf("\n\tError en la apertura del archivo");
		return 1;
	}
	printf("\n\tNombre del archivo: %s\n",nombre);	
	printf("\n\tContenido del archivo");
	printf("\n\t----------------------\n");
	while ((c = fgetc(archivo)) != EOF) 
	{
		if(c == '\n')
		{
			fila++;
		}
		else if(c == ',')
		{	
			coma++;
		}
    	}
	fseek(archivo,0,SEEK_SET);
	char arr[(coma/fila)+1][fila][1000];
	float valor_f[(coma/fila)+1][fila];

	int t=0,u=0;
	do
	{
		fgets(linea, 100, archivo);
		token = strtok(linea, ",");

    		while(token != NULL) 
		{
			if (strchr(token, '\n') != NULL) 
			{
            			token[strcspn(token, "\n")] = '\0';
        		}
			strcpy(arr[t][u], token);
        		token = strtok(NULL, ","); 
			t++;
    		}
		u++;
		t=0;
	}
	while(!feof(archivo));
	
	float suma[(coma/fila)+1];
	float promedio[(coma/fila)+1];
	float varianza[(coma/fila)+1];
	float desviacion[(coma/fila)+1];

	for(i=0;i<(coma/fila)+1;i++) 
	{
        	suma[i] = 0.0;
		promedio[i] = 0.0;
		varianza[i] = 0.0;
		desviacion[i] = 0.0;
    	}

	for (t=0;t<(coma/fila)+1;t++) 
	{
		printf("\n\tColumna %d:\n\n\t[",t+1);
        	for (u=0;u<fila;u++) 
		{
			printf("%s,",arr[t][u]);
			valor_f[t][u] = atof(arr[t][u]);
			suma[t] = suma[t] + valor_f[t][u];
        	}
		printf("]\n");
    	} 	
	printf("\n\n\tOperaciones:\n");
	for(i=0;i<(coma/fila)+1;i++) 
	{
        	promedio[i] = suma[i]/fila;
		printf("\n\tPromedio de la columna %d: %.1f",i+1,promedio[i]);
    	}
	printf("\n");
	for(t=0;t<(coma/fila)+1;t++)	
	{
		for(i=0;i<fila;i++) 
		{
			varianza[t] = varianza[t] + (pow((valor_f[t][i] - promedio[t]),2))/fila;
    		}
		printf("\n\tVarianza de la columna %d: %.1f",t+1,varianza[t]);
	}
	printf("\n");
	for(i=0;i<(coma/fila)+1;i++) 
	{
        	desviacion[i] = sqrt(varianza[i]);
		printf("\n\tDesviacion estandar de la columna %d: %.1f",i+1,desviacion[i]);
    	}
	printf("\n");

    	fclose(archivo);

	return 0;
}