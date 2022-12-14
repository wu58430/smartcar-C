/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file            zf_common_fifo
 * @company         成都逐飞科技有限公司
 * @author          逐飞科技(QQ790875685)
 * @version         查看doc内version文件 版本说明
 * @Software        MounRiver Studio V1.51
 * @Target core     CH32V307VCT6
 * @Taobao          https://seekfree.taobao.com/
 * @date            2021-11-11
 * @note            version:
 *                  V1.1 2021.6.23 读取与写入函数加入关闭中断的操作，避免读取的时候被写入打断，导致剩余空间计算错误。
 *                  V1.2 2021.7.06 修复读取与写入函数，尾指针到尾部距离  类型定义错误
********************************************************************************************************************/

#ifndef _zf_common_fifo_h_
#define _zf_common_fifo_h_

#include "stdint.h"
#include "string.h"

typedef struct
{
    uint8_t     *buffer;                                                        // 缓存指针
    uint32_t    head;                                                           // 缓存头指针 总是指向空的缓存
    uint32_t    end;                                                            // 缓存尾指针 总是指向非空缓存（缓存全空除外）
    uint32_t    size;                                                           // 缓存剩余大小
    uint32_t    max;                                                            // 缓存总大小
}fifo_struct;

typedef enum
{
    FIFO_SUCCESS,

    FIFO_BUFFER_NULL,
    FIFO_SPACE_NO_ENOUGH,
    FIFO_DATA_NO_ENOUGH,
}fifo_state_enum;

typedef enum
{
    FIFO_READ_AND_CLEAN,
    FIFO_READ_ONLY,
}fifo_operation_enum;

fifo_state_enum fifo_init           (fifo_struct *fifo, uint8_t *buffer_addr, uint32_t size);
void            fifo_head_offset    (fifo_struct *fifo, uint32_t offset);
void            fifo_end_offset     (fifo_struct *fifo, uint32_t offset);
void            fifo_clean          (fifo_struct *fifo);
uint32_t        fifo_used           (fifo_struct *fifo);

fifo_state_enum fifo_read_buffer    (fifo_struct *fifo, uint8_t *dat, uint32_t *length, fifo_operation_enum flag);
fifo_state_enum fifo_write_buffer   (fifo_struct *fifo, uint8_t *dat, uint32_t length);

#endif
