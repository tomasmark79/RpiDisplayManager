#ifndef __DISPLAYBROKER_H__
#define __DISPLAYBROKER_H__

class DisplayBroker
{
public:
    DisplayBroker();
    ~DisplayBroker();

private:
// Funkce pro přepnutí kanálu na TCA9548A
  int selectI2CDevice(int fd, int channel);
};

#endif // __DISPLAYBROKER_H__