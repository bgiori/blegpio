/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "bsp/bsp.h"
#include "hal/hal_gpio.h"
#include "console/console.h"
#include "host/ble_hs.h"
#include "bleprph.h"

/**
 * The vendor specific security test service consists of two characteristics:
 *     o random-number-generator: generates a random 32-bit number each time
 *       it is read.  This characteristic can only be read over an encrypted
 *       connection.
 *     o static-value: a single-byte characteristic that can always be read,
 *       but can only be written over an encrypted connection.
 */

/* 59462f12-9543-9999-12c8-58b459a2712d */
const uint8_t gatt_svr_svc_gpio[16] = {
    0x2b, 0x71, 0xa2, 0x59, 0xb4, 0x58, 0xc8, 0x12,
    0x99, 0x99, 0x43, 0x95, 0x12, 0x2f, 0x46, 0x59
};

/* 5c3a659e-897e-45e1-b016-007107c96df7 */
const uint8_t gatt_svr_chr_gpio[16] = {
    0xb7, 0x6d, 0xc9, 0x07, 0x71, 0x00, 0x16, 0xb0,
    0xe1, 0x45, 0x7e, 0x89, 0x9e, 0x65, 0x3a, 0x5c
};

/* 5c3a659e-897e-45e1-b016-007107c96df8 */
const uint8_t gatt_svr_chr_gpio_notif[16] = {
    0xb8, 0x6d, 0xc9, 0x07, 0x71, 0x00, 0x16, 0xb0,
    0xe1, 0x45, 0x7e, 0x89, 0x9e, 0x65, 0x3a, 0x5c
};

/* GPIO Instruction message */
static uint16_t gatt_svr_gpio_instr;
static uint16_t gatt_svr_gpio_read_val;
static uint16_t gatt_svr_chr_gpio_notif_val_handle;


/* To keep track of GPIO pin inits and values */
static uint8_t pin_inits[32];
static uint8_t pin_vals[32];

/* Array to keep track of initializations */
#define GPIO_UNINITIALIZED      (0)

/* Define input/output constants */
#define GPIO_INPUT              (2)
#define GPIO_OUTPUT             (1)


static int
gatt_svr_chr_access_alert(uint16_t conn_handle, uint16_t attr_handle,
                          struct ble_gatt_access_ctxt *ctxt,
                          void *arg);


static int
gatt_svr_chr_access_gpio(uint16_t conn_handle, uint16_t attr_handle,  
                         struct ble_gatt_access_ctxt *ctxt, 
                         void *arg);

static int
gatt_svr_chr_access_gpio_notif(uint16_t conn_handle, uint16_t attr_handle, 
                               struct ble_gatt_access_ctxt *ctxt, 
                               void *arg);


static const struct ble_gatt_svc_def gatt_svr_svcs[] = {
    {
        /*** Alert Notification Service. */
        .type = BLE_GATT_SVC_TYPE_PRIMARY,
        .uuid128 = BLE_UUID16(GATT_SVR_SVC_ALERT_UUID),
        .characteristics = (struct ble_gatt_chr_def[]) { {
            .uuid128 = BLE_UUID16(GATT_SVR_CHR_SUP_NEW_ALERT_CAT_UUID),
            .access_cb = gatt_svr_chr_access_alert,
            .flags = BLE_GATT_CHR_F_READ,
        }, {
            .uuid128 = BLE_UUID16(GATT_SVR_CHR_NEW_ALERT),
            .access_cb = gatt_svr_chr_access_alert,
            .flags = BLE_GATT_CHR_F_NOTIFY,
        }, {
            .uuid128 = BLE_UUID16(GATT_SVR_CHR_SUP_UNR_ALERT_CAT_UUID),
            .access_cb = gatt_svr_chr_access_alert,
            .flags = BLE_GATT_CHR_F_READ,
        }, {
            .uuid128 = BLE_UUID16(GATT_SVR_CHR_UNR_ALERT_STAT_UUID),
            .access_cb = gatt_svr_chr_access_alert,
            .flags = BLE_GATT_CHR_F_NOTIFY,
        }, {
            .uuid128 = BLE_UUID16(GATT_SVR_CHR_ALERT_NOT_CTRL_PT),
            .access_cb = gatt_svr_chr_access_alert,
            .flags = BLE_GATT_CHR_F_WRITE,
        }, {
            0, /* No more characteristics in this service. */
        } },
    },

    {
        /* GPIO Service */
        .type = BLE_GATT_SVC_TYPE_PRIMARY,
        .uuid128 = (void *)gatt_svr_svc_gpio,
        .characteristics = (struct ble_gatt_chr_def[]) { {
            /* GPIO Read/Write Characteristic. See 
             * gatt_svr_chr_access_gpio definition for explanation */
            .uuid128 = (void *)gatt_svr_chr_gpio,
            .access_cb = gatt_svr_chr_access_gpio,
            .flags = BLE_GATT_CHR_F_WRITE | BLE_GATT_CHR_F_READ,
        }, {
            .uuid128 = (void *)gatt_svr_chr_gpio_notif,
            .access_cb = gatt_svr_chr_access_gpio_notif,
            .flags = BLE_GATT_CHR_F_NOTIFY,
            .val_handle = &gatt_svr_chr_gpio_notif_val_handle,
        }, {
            0, /* No more characteristics in this service. */
        } },
    },

    {
        0, /* No more services. */
    },
};

static int
gatt_svr_chr_write(uint8_t op, struct ble_gatt_access_ctxt *ctxt,
                   uint16_t min_len, uint16_t max_len, void *dst,
                   uint16_t *len)
{
    assert(op == BLE_GATT_ACCESS_OP_WRITE_CHR);
    if (ctxt->att->write.len < min_len ||
        ctxt->att->write.len > max_len) {

        return BLE_ATT_ERR_INVALID_ATTR_VALUE_LEN;
    }

    memcpy(dst, ctxt->att->write.data, ctxt->att->write.len);
    if (len != NULL) {
        *len = ctxt->att->write.len;
    }

    return 0;
}

#define GATT_SVR_NEW_ALERT_VAL_MAX_LEN    64

static const uint8_t gatt_svr_new_alert_cat = 0x01; /* Simple alert. */
static uint8_t gatt_svr_new_alert_val[GATT_SVR_NEW_ALERT_VAL_MAX_LEN];
static uint16_t gatt_svr_new_alert_val_len;
static const uint8_t gatt_svr_unr_alert_cat = 0x01; /* Simple alert. */
static uint16_t gatt_svr_unr_alert_stat;
static uint16_t gatt_svr_alert_not_ctrl_pt;

static int
gatt_svr_chr_access_alert(uint16_t conn_handle, uint16_t attr_handle,
                          struct ble_gatt_access_ctxt *ctxt,
                          void *arg)
{
    uint16_t uuid16;
    int rc;

    uuid16 = ble_uuid_128_to_16(ctxt->chr->uuid128);
    assert(uuid16 != 0);

    switch (uuid16) {
    case GATT_SVR_CHR_SUP_NEW_ALERT_CAT_UUID:
        assert(ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR);
        ctxt->att->read.data = &gatt_svr_new_alert_cat;
        ctxt->att->read.len = sizeof gatt_svr_new_alert_cat;
        return 0;

    case GATT_SVR_CHR_NEW_ALERT:
        if (ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR) {
            rc = gatt_svr_chr_write(ctxt->op, ctxt, 0,
                                    sizeof gatt_svr_new_alert_val,
                                    gatt_svr_new_alert_val,
                                    &gatt_svr_new_alert_val_len);
            return rc;
        } else if (ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR) {
            ctxt->att->read.data = (void *)&gatt_svr_new_alert_val;
            ctxt->att->read.len = sizeof gatt_svr_new_alert_val;
            return 0;
        }

    case GATT_SVR_CHR_SUP_UNR_ALERT_CAT_UUID:
        assert(ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR);
        ctxt->att->read.data = &gatt_svr_unr_alert_cat;
        ctxt->att->read.len = sizeof gatt_svr_unr_alert_cat;
        return 0;

    case GATT_SVR_CHR_UNR_ALERT_STAT_UUID:
        if (ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR) {
            rc = gatt_svr_chr_write(ctxt->op, ctxt, 2, 2,
                                    &gatt_svr_unr_alert_stat,
                                    NULL);
        } else {
            ctxt->att->read.data = &gatt_svr_unr_alert_stat;
            ctxt->att->read.len = sizeof gatt_svr_unr_alert_stat;
            rc = 0;
        }
        return rc;

    case GATT_SVR_CHR_ALERT_NOT_CTRL_PT:
        if (ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR) {
            rc = gatt_svr_chr_write(ctxt->op, ctxt, 2, 2,
                                    &gatt_svr_alert_not_ctrl_pt, NULL);
        } else {
            rc = BLE_ATT_ERR_UNLIKELY;
        }
        return rc;

    default:
        assert(0);
        return BLE_ATT_ERR_UNLIKELY;
    }
}

/** gatt_svr_chr_access_gpio
 *
 * This function handles read and write access for the GPIO 
 * Characteristic. This function handles both reading to and writing
 * from a pin as well as initializing the pin if needed.Applications 
 * can access the the GPIO through by writing an instruction 
 * to this characteristic. 
 *
 * The Instruction is 16 bits (2 bytes) and should be set up as follows:
 *
 *      [31:16]  Pin number     (e.g. Pin 17 --> 0x11)
 *      [15:8]   Direction      (Input = 2; Output = 1)
 *      [7:0]    Value          (Low = 0; High = 1 (or not zero))
 *
 * Sample write instruction:    0x1D11 (Write 1 to pin 29)
 * Sample read instruction:     0x0420 (Read from pin 4)
 * 
 * This function first parses the instruction into its three parts
 * as defined above and acts accordingly. We first check the direction
 * to determine if the instruction is read or write. A read instruction
 * will access and input pin and a write instruction will access 
 * an output pin. Next, we check if the pin has been initialized yet; if
 * not, initialize the pin accordingly. Finally we read/write the pin
 * and return.
 */ 
static int
gatt_svr_chr_access_gpio(uint16_t conn_handle, uint16_t attr_handle,
                            struct ble_gatt_access_ctxt *ctxt, void *arg)
{
    void const *uuid128;
    uint8_t op;
    int rc;

    uuid128 = ctxt->chr->uuid128;
    op = ctxt->op;
     
    /* Check that the UUID is correct */
    if (memcmp(uuid128, gatt_svr_chr_gpio, 16) == 0) {
        /* Use the op to determine whether access is read/write */
        switch (op) {
        case BLE_GATT_ACCESS_OP_READ_CHR:
            /* Read access */
            assert( op == BLE_GATT_ACCESS_OP_READ_CHR);
            /* Set the chr_access data and length fields */
            ctxt->att->read.data = &gatt_svr_gpio_read_val;
            ctxt->att->read.len = sizeof gatt_svr_gpio_read_val;
            return 0;

        case BLE_GATT_ACCESS_OP_WRITE_CHR:
            /* Write access */
            assert(op == BLE_GATT_ACCESS_OP_WRITE_CHR);
            /* Write received data to gpio instr field */ 
            rc = gatt_svr_chr_write(op, ctxt,
                                    sizeof gatt_svr_gpio_instr,
                                    sizeof gatt_svr_gpio_instr,
                                    &gatt_svr_gpio_instr, NULL);
            assert(rc == 0);
            /* Parse instruction into parts */
            uint8_t pin = gatt_svr_gpio_instr >> 8;
            uint8_t dir = (gatt_svr_gpio_instr & 0x00f0) >> 4;
            uint32_t val = gatt_svr_gpio_instr & 0x000f;
            BLEPRPH_LOG(INFO, "Instruction received: pin=%u, dir=%u, " \
                                "val=%u\n", pin, dir, val);
            
            assert(pin < 32 && pin >= 0);
            /* Determine input/output from instruction direction */
            if (dir == GPIO_OUTPUT) {
                /* Check if output pin has been initialized yet */
                if(pin_inits[pin] ==  GPIO_UNINITIALIZED) {
                    pin_inits[pin] = GPIO_OUTPUT;
                    BLEPRPH_LOG(INFO, "Setting Pin %d as output...\n", pin);
                    rc = hal_gpio_init_out(pin, val);
                    assert(rc == 0);
                } else {
                    /* If pin has been initialized, write val to pin */
                    hal_gpio_write(pin, val);
                }
            } else if (dir == GPIO_INPUT) {
                /* Check if input pin has ben initialized yet */
                if(pin_inits[pin] == GPIO_UNINITIALIZED) {
                    pin_inits[pin] = GPIO_INPUT;
                    BLEPRPH_LOG(INFO, "Setting Pin %d as input...\n", pin);
                    rc = hal_gpio_init_in(pin, val);
                    assert(rc == 0);
                }
                /* Every instruction to an input pin should write the
                 * pin value to gatt_svr_read_val */
                uint16_t val = hal_gpio_read(pin) ? 1 : 0;
                pin_vals[pin] = val;
                memcpy(&gatt_svr_gpio_read_val, &val, sizeof val);
            } else {
                /* Invalid direction */
                assert(0);
                return BLE_ATT_ERR_UNLIKELY; 
            }
            return rc;
        default:
            assert(0);
            return BLE_ATT_ERR_UNLIKELY;
        }
    }
    /* Unknown characteristic; the nimble stack should not have called this
     * function.
     */
    assert(0);
    return BLE_ATT_ERR_UNLIKELY;
}

/**
 * The task function for io_poll_task defined in main.c. This function 
 * will wait on an event which comes when we encounter a new subsciber
 * then loop through all the input pins looking for changes in values.
 * If a discrepency is found, notify the client with the pin's info.
 */
void
io_poll_task_handler(void *unused)
{
    int rc; 
    /* Wait for an initial subscriber to start polling I/O */
    os_eventq_get(&io_poll_evq);
    while (1) {
        /* Get the connection handle */
        uint16_t conn_handle = get_conn_handle();
        /* Wait 1/4 sec */
        os_time_delay(OS_TICKS_PER_SEC/4);
        int i;
        /* Loop through gpio input pins */
        for (i = 0; i < (sizeof(pin_inits)/sizeof(uint8_t)); i++) {
            if (pin_inits[i] == GPIO_INPUT) {
                uint16_t val = hal_gpio_read(i) ? 1 : 0;
                /* Check for discrepencies in read value and stored value */
                if (pin_vals[i] != val) {
                    BLEPRPH_LOG(DEBUG, "Found discrepency on pin: %d\n", i);
                    /* Construct info to send to client. Same structure as
                     * instruction defined in gatt_svr_chr_access_gpio */
                    uint16_t pinfo = (i << 8) + 0x20 + val;
                    const void *pinfo_ptr = &pinfo;
                    /* Notify */
                    rc = ble_gattc_notify_custom(conn_handle, 
                                            gatt_svr_chr_gpio_notif_val_handle,
                                            pinfo_ptr, sizeof(pinfo));
                    /* If the notification was successful, update 
                     * stored pin val */
                    if (rc == 0) {
                        pin_vals[i] = val;
                    }
                }
            }
        }   
    }   
}

/**
 * This should never be called
 */
static int
gatt_svr_chr_access_gpio_notif(uint16_t conn_handle, uint16_t attr_handle, 
                               struct ble_gatt_access_ctxt *ctxt, void *arg)
{
    assert(0);
    return BLE_ATT_ERR_UNLIKELY; 
}

static char *
gatt_svr_uuid_to_s(const void *uuid128, char *dst)
{
    const uint8_t *u8p;
    uint16_t uuid16;

    uuid16 = ble_uuid_128_to_16(uuid128);
    if (uuid16 != 0) {
        sprintf(dst, "0x%04x", uuid16);
        return dst;
    }

    u8p = uuid128;

    sprintf(dst,      "%02x%02x%02x%02x-", u8p[15], u8p[14], u8p[13], u8p[12]);
    sprintf(dst + 9,  "%02x%02x-%02x%02x-", u8p[11], u8p[10], u8p[9], u8p[8]);
    sprintf(dst + 19, "%02x%02x%02x%02x%02x%02x%02x%02x",
            u8p[7], u8p[6], u8p[5], u8p[4], u8p[3], u8p[2], u8p[1], u8p[0]);

    return dst;
}

static void
gatt_svr_register_cb(struct ble_gatt_register_ctxt *ctxt, void *arg)
{
    char buf[40];

    switch (ctxt->op) {
    case BLE_GATT_REGISTER_OP_SVC:
        BLEPRPH_LOG(DEBUG, "registered service %s with handle=%d\n",
                    gatt_svr_uuid_to_s(ctxt->svc.svc_def->uuid128, buf),
                    ctxt->svc.handle);
        break;

    case BLE_GATT_REGISTER_OP_CHR:
        BLEPRPH_LOG(DEBUG, "registering characteristic %s with "
                           "def_handle=%d val_handle=%d\n",
                    gatt_svr_uuid_to_s(ctxt->chr.chr_def->uuid128, buf),
                    ctxt->chr.def_handle,
                    ctxt->chr.val_handle);
        break;

    case BLE_GATT_REGISTER_OP_DSC:
        BLEPRPH_LOG(DEBUG, "registering descriptor %s with handle=%d\n",
                    gatt_svr_uuid_to_s(ctxt->dsc.dsc_def->uuid128, buf),
                    ctxt->dsc.handle);
        break;

    default:
        assert(0);
        break;
    }
}

int
gatt_svr_register(void)
{
    int rc;

    rc = ble_gatts_register_svcs(gatt_svr_svcs, gatt_svr_register_cb, NULL);
    return rc;
}

int
gatt_svr_init(struct ble_hs_cfg *cfg)
{
    int rc;

    rc = ble_gatts_count_cfg(gatt_svr_svcs, cfg);
    if (rc != 0) {
        return rc;
    }

    return 0;
}
