arm-none-eabi-gcc -c -o /Users/briangiori/dev/newt/blegpio/bin/nrf52_boot/libs/mbedtls/ccm.o ccm.c -DAPP_NAME="boot" -DARCH_cortex_m4 -DBSP_HAS_32768_XTAL -DBSP_NAME="nrf52dk" -DLOG_LEVEL=255 -DMBEDTLS_USER_CONFIG_FILE=\"mbedtls/config_mynewt.h\" -DNFFS_PRESENT -DNRF52 -Os -Wall -Werror -fdata-sections -ffunction-sections -fno-exceptions -ggdb -mcpu=cortex-m4 -mthumb -mthumb-interwork -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/apps/boot//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/apps/boot//include/boot/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/apps/boot//src/ -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/apps/boot//src//arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/compiler/arm-none-eabi-m4//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/compiler/arm-none-eabi-m4//include/arm-none-eabi-m4/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/fs/fs//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/fs/fs//include/fs/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/fs/nffs//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/fs/nffs//include/nffs/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/hw/bsp/nrf52dk//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/hw/bsp/nrf52dk//include/nrf52dk/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/hw/bsp/nrf52dk//src/ -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/hw/bsp/nrf52dk//src//arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/hw/hal//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/hw/hal//include/hal/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx//include/nrf52xxx/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/baselibc//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/baselibc//include/baselibc/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/bootutil//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/bootutil//include/bootutil/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/cmsis-core//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/cmsis-core//include/cmsis-core/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/console/stub//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/console/stub//include/stub/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/mbedtls//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/mbedtls//include/mbedtls/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/mbedtls//src/ -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/mbedtls//src//arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/os//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/os//include/os/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/testutil//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/testutil//include/testutil/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/util//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/util//include/util/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/sys/config//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/sys/config//include/config/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/sys/log//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/sys/log//include/log/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/targets/nrf52_boot//include -I/Users/briangiori/dev/newt/blegpio/targets/nrf52_boot//include/nrf52_boot/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/targets/nrf52_boot//src/ -I/Users/briangiori/dev/newt/blegpio/targets/nrf52_boot//src//arch/cortex_m4