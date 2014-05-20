#ifndef _READ_RFID_H_
#define _READ_RFID_H_

int rfid_read(int serialfd ,char *cardID,int hub_index);
int rfid_open(void);
#endif
