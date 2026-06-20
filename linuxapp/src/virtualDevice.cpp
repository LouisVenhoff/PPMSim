#include "virtualDevice.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <linux/uinput.h>

int fd;

void virtualDeviceInit(){

  fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

  if(fd < 0){
    std::cout << "Failed to open uinput device" << std::endl;
    return;
  }
  //Activate virtual device
  ioctl(fd, UI_SET_EVBIT, EV_KEY);
  
  //Activate axes
  ioctl(fd, UI_SET_ABSBIT, ABS_X);
  ioctl(fd, UI_SET_ABSBIT, ABS_Y);
  ioctl(fd, UI_SET_ABSBIT, ABS_RX);
  ioctl(fd, UI_SET_ABSBIT, ABS_RY);

  struct uinput_user_dev uidev;
  memset(&uidev, 0, sizeof(uidev));

  //Create virtual device here
  snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "PPMSim");
  uidev.id.bustype = BUS_USB;
  uidev.id.vendor = 0x1234;
  uidev.id.product = 0x5678;
  uidev.id.version = 1;

  //Define control range
  uidev.absmin[ABS_X] = MIN_AXIS;
  uidev.absmax[ABS_X] = MAX_AXIS;
  uidev.absmin[ABS_Y] = MIN_AXIS;
  uidev.absmax[ABS_Y] = MAX_AXIS;
  uidev.absmin[ABS_RX] = MIN_AXIS;
  uidev.absmax[ABS_RX] = MAX_AXIS;
  uidev.absmin[ABS_RY] = MIN_AXIS;
  uidev.absmax[ABS_RY] = MAX_AXIS;

  //Send device to Kernel
  write(fd, &uidev, sizeof(uidev));

  //Create device
  ioctl(fd, UI_DEV_CREATE);
}

void virtualDeviceUpdate(char *controls){
  std::cout << "Updating virtual device with controls: " << controls << std::endl;
}