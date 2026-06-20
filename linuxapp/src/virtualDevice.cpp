#include "virtualDevice.h"

int fd;

struct controls{
  uint16_t throttle;
  uint16_t roll;
  uint16_t yaw;
  uint16_t pitch;
};

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

  sleep(1); 
}

int parseControls(char* rawControls, controls* c){
  
  nlohmann::json j = nlohmann::json::parse(rawControls);

  c->throttle = j[CH1];
  c->roll = j[CH2];
  c->yaw = j[CH3];
  c->pitch = j[CH4];

  return 0;
  
};

void virtualDeviceUpdate(char *rawControls){

  controls c;

  int result = parseControls(rawControls, &c);

  if(result < 0){
    std::cout << "Error while parsing controls!" << std::endl;
    return;
  }

  struct input_event ev_x;
  struct input_event ev_y;
  struct input_event ev_rx;
  struct input_event ev_ry;
  struct input_event ev_syn;
  
  memset(&ev_x, 0, sizeof(ev_x));
  memset(&ev_y, 0, sizeof(ev_y));
  memset(&ev_rx, 0, sizeof(ev_rx));
  memset(&ev_ry, 0, sizeof(ev_ry));
  memset(&ev_syn, 0, sizeof(ev_syn));

  ev_x.type = EV_ABS;
  ev_y.type = EV_ABS;
  ev_rx.type = EV_ABS;
  ev_ry.type = EV_ABS;
  ev_syn.type = EV_SYN;

  ev_x.code = ABS_X;
  ev_y.code = ABS_Y;
  ev_rx.code = ABS_RX;
  ev_ry.code = ABS_RY;
  ev_syn.code = SYN_REPORT;

  ev_syn.value = 0;
  ev_x.value = c.throttle;
  ev_y.value = c.yaw;
  ev_rx.value = c.roll;
  ev_ry.value = c.pitch;

  write(fd, &ev_x, sizeof(ev_x));
  write(fd, &ev_y, sizeof(ev_y));
  write(fd, &ev_rx, sizeof(ev_rx));
  write(fd, &ev_ry, sizeof(ev_ry));
  write(fd, &ev_syn, sizeof(ev_syn));



  //std::cout << "Updating virtual device with controls: " << c.throttle << ", " << c.roll << ", " << c.yaw << ", " << c.pitch << std::endl;
}