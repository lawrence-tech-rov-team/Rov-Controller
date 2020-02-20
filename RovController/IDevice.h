/*
 * IDevice.h
 *
 * Created: 2/2/2020 6:21:04 PM
 *  Author: zcarey
 */ 


#ifndef IDEVICE_H_
#define IDEVICE_H_


class IDevice{
public:
	uint8_t getId(){
		return id;
	}
	
	virtual void Update(const uint8_t* data, uint8_t len) = 0;
	virtual bool begin() = 0;
	
protected:
	IDevice(uint8_t ID) : id(ID){
		
	}
	
private:
	uint8_t id;
};



#endif /* IDEVICE_H_ */