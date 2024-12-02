#ifndef __DISPLAYBROKER_H__
#define __DISPLAYBROKER_H__

class DisplayBroker
{
  public:
    DisplayBroker();
    ~DisplayBroker();

  private:

    int selectI2CChannel(int channel);

    bool SetupTest();
    void EndTest();
    void TestLoop();

    int use_u8g2();
};

#endif // __DISPLAYBROKER_H__