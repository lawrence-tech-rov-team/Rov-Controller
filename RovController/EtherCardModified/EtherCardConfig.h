#ifndef ETHER_CARD_CONFIG_H
#define ETHER_CARD_CONFIG_H

//---Definitions----------------------------------------------------------------------------------------------//
#define ETHER_CARD_BUFFER_SIZE 512


//---Checks----------------------------------------------------------------------------------------------//
#ifndef ETHER_CARD_BUFFER_SIZE
	#warning "ETHER_CARD_BUFFER_SIZE" is not defined in the "EtherCardConfig.h" config file. using 512 by default.
	#define ETHER_CARD_BUFFER_SIZE 512
#elif ETHER_CARD_BUFFER_SIZE > 512
	#warning "ETHER_CARD_BUFFER_SIZE" is too large, truncating to 512.
	#undef ETHER_CARD_BUFFER_SIZE
	#define ETHER_CARD_BUFFER_SIZE 512
#endif



#endif //ETHER_CARD_CONFIG_H