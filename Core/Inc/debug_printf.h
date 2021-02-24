//
// Created by kaylor on 2021/2/23.
//

#ifndef DEBUG_PRINTF_H
#define DEBUG_PRINTF_H

//#define __DEBUG__
#ifdef __DEBUG__
//#define DEBUG_PRINTF(format,...)    printf("File: "__FILE__", Line: %05d: "format"/n", __LINE__, ##__VA_ARGS__)
#define DEBUG_PRINTF(format,...)    printf(format, ##__VA_ARGS__)

#else
#define DEBUG_PRINTF(format,...)
#endif

#endif //FATFS_STM32_DEBUG_PRINTF_H
