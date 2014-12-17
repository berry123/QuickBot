#include <stdio.h>

void main(){
	char sensLimit = 2;
	char TS;
	char FSS;
	char BSS;
	char RSS;
	char LSS;
	FSS = (sensLimit < 1);
	BSS = (sensLimit < 2);
	RSS = (sensLimit < 3);
	LSS = (sensLimit < 4);
	TS = FSS + BSS + RSS + LSS;

	printf("%d",TS);

}
