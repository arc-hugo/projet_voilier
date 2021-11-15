#include "Voile.h"
#include "Orientation.h"
#include "Communication.h"
#include "Batterie.h"

int main(void){
	Voile_Init();
	Batterie_Init();
	Orientation_Init();
	Communication_Init();

	while(1);
}	
