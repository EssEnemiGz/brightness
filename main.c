#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv){ // argc Counter Args and argv Array Argv
	FILE *FR, *FW;
	int uid, toSum1, toSum2, finalNum;
	char product[30];
	char str[30];

	FR = fopen("/sys/class/backlight/intel_backlight/brightness", "r");
	FW = fopen("/sys/class/backlight/intel_backlight/brightness", "w");
	uid = getuid();
	
	// Error conditions
	if (FR == NULL){
		perror("\033[31mFile error \033[0m");
		return 1;
	}
	else if (argc < 2 && argv[1] != "-c"){
		puts("\033[31mDebe introducir argumentos. \033[0m");
		return 1;
	}
	else if (uid){
		puts("\033[31mInicie el programa desde el usuario root. \033[0m");
		return 1;
	};

	// Conditionals for arguments
	fread(str, 1, 30, FR);
	toSum2 = atoi(str); // The actual brightness 
	
	if (!strcmp(argv[1], "-u")){
		toSum1 = atoi(argv[2]); // The brightness that the user request
		sprintf(product, "%i", toSum1+toSum2);

		fwrite(product, 1, strlen(product), FW);
		printf("\033[32m El brillo actual es: %s \033[0m\n", product);
		return 0;
	}
	else if(!strcmp(argv[1], "-d")){
		toSum1 = atoi(argv[2]); // The brightness that the user request
		if (toSum1 > toSum2){
			finalNum = toSum1-toSum2;
		}else{
			finalNum = toSum2-toSum1;
		};

		sprintf(product, "%i", finalNum);

		fwrite(product, 1, strlen(product), FW);
		printf("\033[31m El brillo actual es %s \033[0m\n", product);
		return 0;
	}
	else if(!strcmp(argv[1], "-c")){
		printf("\033[33m El brillo actual es: %s \033[0m", str);
	}
	else{
		puts("\033[31m ERROR:\033[0m ¡Argumento desconocido!");
	};

	fclose(FR);
	fclose(FW);
	return 0;
}
