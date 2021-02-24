//
// Created by kaylor on 2021/2/23.
//
#include "stdio.h"
#include "fatfs.h"
#include "tftp_server.h"
#include "debug_printf.h"
#include "tftpserverif.h"

static void *openfile(const char *fname, const char *mode, u8_t write);

static void closefile(void *handle);

int readfile(void *handle, void *buf, int bytes);

int writefile(void *handle, struct pbuf *p);

const struct tftp_context tftpContext = {
        openfile,
        closefile,
        readfile,
        writefile,
};

void tftpserverif_init(void) {
  retSD = f_mount(&SDFatFS, "", 0);
  if (retSD) {
    DEBUG_PRINTF("mount error : %d \r\n", retSD);
    Error_Handler();
  } else
    DEBUG_PRINTF("mount success!!! \r\n");
  DIR dir_1;
  retSD = f_opendir(&dir_1, "/");
  if ( retSD != FR_OK)
  {
    DEBUG_PRINTF("opendir error: %d\r\n", retSD);
    return;
  } else{
    DEBUG_PRINTF("opendir success!!! \r\n");
  }
  if(tftp_init(&tftpContext) == ERR_OK)
  {
    DEBUG_PRINTF("TFTP init success\r\n");
  }
  else
  {
    DEBUG_PRINTF("TFTP init error\r\n");
  }
}

static void *openfile(const char *fname, const char *mode, u8_t write) {
  DEBUG_PRINTF("filename =%s, mode = %s, rw = %d\r\n", fname, mode, write);
  if (write != 0)
    retSD = f_open(&SDFile, fname, FA_CREATE_ALWAYS | FA_WRITE);
  else
    retSD = f_open(&SDFile, fname, FA_READ);
  if (retSD) {
    DEBUG_PRINTF("open file error : %d\r\n", retSD);
    return NULL;
  } else {
    DEBUG_PRINTF("open file success!!! \r\n");
    return (void *)&SDFile;
  }
}

static void closefile(void *handle) {
  do {
    retSD = f_close(handle);
    DEBUG_PRINTF("closing file\r\n");
  } while (retSD);
  DEBUG_PRINTF("close success!!! \r\n");
}

int readfile(void *handle, void *buf, int bytes) {
  uint32_t bytesread;
  retSD = f_read(handle, buf, bytes, (UINT *) &bytesread);
  if (retSD) {
    DEBUG_PRINTF("read error!!! %d\r\n", retSD);
  } else {
    DEBUG_PRINTF("read success!!! bytesread = %d\r\n", bytesread);
  }
  return bytesread;
}
#define TFTP_HEADER_LENGTH (4)
int writefile(void *handle, struct pbuf *p) {
  DEBUG_PRINTF("begin to write ....\r\n");
  DEBUG_PRINTF("len = %d\r\n", p->len);

  int byteswritten;
//  uint8_t wtext[] = "This is STM32 working with FatFs_with_DMA_and_Freertos mode\r\n"; /* File write buffer */
//  retSD = f_write(&SDFile, wtext, sizeof(wtext), (void *)&byteswritten);

  retSD = f_write(handle, (char *)p->payload + TFTP_HEADER_LENGTH , p->len - TFTP_HEADER_LENGTH, (void *) &byteswritten);
  if (retSD) {
    DEBUG_PRINTF("write file error : %d\r\n", retSD);
  } else {
    DEBUG_PRINTF("write file sucess!!!  byteswritten = %d\r\n", byteswritten);
  }
  DEBUG_PRINTF("byteswritten = %d\r\n", byteswritten);
  return byteswritten;
}

