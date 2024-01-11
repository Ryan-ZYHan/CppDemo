#ifndef __WELDMACHINE_H_
#define __WELDMACHINE_H_

class WeldMachine
{
private:
    /* data */
public:
    virtual int OpendDevice() =0;
    virtual int CloseDevice() =0;
    virtual int 
    virtual ~WeldMachine();
};

#endif