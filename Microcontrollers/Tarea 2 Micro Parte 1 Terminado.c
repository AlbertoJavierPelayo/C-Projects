
unsigned char led;

void UART0_IRQHandler()
{
	led=UART0_D;
	//Configuración lógica del sistema
	if (led=='G')	 	//Enciende Led Verde
	{
		GPIOB_PDOR=(0<<19)+(1<<18);
		GPIOD_PDOR=(1<<1);
	}								
	else if(led=='B')	//Enciende Led Azul
	{
		GPIOB_PDOR=(1<<19)+(1<<18);
		GPIOD_PDOR=(0<<1);
	}		
	else if (led=='R')	//Enciende Led Rojo
	{
		GPIOB_PDOR=(1<<19)+(0<<18);
		GPIOD_PDOR=(1<<1);
	}				
	else				//Apaga todo
	{
		GPIOB_PDOR=(1<<19)+(1<<18);
		GPIOD_PDOR=(1<<1);
	}
}

void clk_init (void)
{
	//Configuración de reloj para 4 MHz (código dado)
	MCG_C1|=(1<<6) + (1<<1);
	MCG_C2|=1;
	MCG_SC=0;
	SIM_CLKDIV1=0;
	SIM_SOPT2|=15<<24;
	
}

int main(void)
{
	clk_init();		//Llama a función de reloj
	
	//Habilitación de relojes de interfaz | pag 204,205
	SIM_SCGC4|=(1<<10);						//Habilita reloj de interfaz de UART0 | pag 204
	SIM_SCGC5|=(1<<12)+(1<<10)+(1<<9);		//Habilita relojes de interfaz de Puertos D, B y A | pag 205
	
	//Configuración de función de puertos | pag 161
	PORTD_PCR1=(1<<8);		//Pin configurado para Led Azul
	
	PORTB_PCR18=(1<<8);		//Pin configurado para Led Rojo
	PORTB_PCR19=(1<<8);		//Pin configurado para Led Verde
	
	PORTA_PCR1=(2<<8);		//Configura pin A para Recepción
	PORTA_PCR2=(2<<8);		//Configura pin A para Transmisión
	
	//Configuración GPIO
	GPIOB_PDDR=(1<<19)+(1<<18); //Configuración de Pin para Salida Puerto B (GPIO) 778
	GPIOD_PDDR=(1<<1);			//Configuración de Pin para Salida Puerto D (GPIO)
	
	//Configuración Baud Rate
	UART0_BDL=26;		//Configura Baud Rate a 9600 bps
	
	UART0_S1|=0x1F;		//Limpiar valor de UART para transmisión (código dado)
	do{
		UART0_S1|=0x1F;
		if ((UART0_S1 & (1<<5))!=0) led=UART0_D;
	}while ((UART0_S1)!=0xC0);
		
	//espacio
	
	
	//Configuración de UART y NVIC
	UART0_C2=(1<<2)+(1<<5);	//Configura UART para transmisión e interrupción
	NVIC_ISER=(1<<12);		//Configuración de interrupción de UART
	
	
	while(1)
	{
	}
	return 0;
}