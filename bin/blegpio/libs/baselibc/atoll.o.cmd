arm-none-eabi-gcc -c -o /Users/briangiori/dev/newt/blegpio/bin/blegpio/libs/baselibc/atoll.o atoll.c -DAPP_NAME="blegpio" -DARCH_cortex_m4 -DBSP_HAS_32768_XTAL -DBSP_NAME="nrf52dk" -DNRF52 -Os -Wall -Werror -fdata-sections -ffunction-sections -fno-exceptions -ggdb -mcpu=cortex-m4 -mthumb -mthumb-interwork -I/Users/briangiori/dev/newt/blegpio/apps/blegpio//include -I/Users/briangiori/dev/newt/blegpio/apps/blegpio//include/blegpio/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/apps/blegpio//src/ -I/Users/briangiori/dev/newt/blegpio/apps/blegpio//src//arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/compiler/arm-none-eabi-m4//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/compiler/arm-none-eabi-m4//include/arm-none-eabi-m4/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/hw/bsp/nrf52dk//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/hw/bsp/nrf52dk//include/nrf52dk/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/hw/bsp/nrf52dk//src/ -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/hw/bsp/nrf52dk//src//arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/hw/hal//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/hw/hal//include/hal/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx//include/nrf52xxx/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/baselibc//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/baselibc//include/baselibc/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/baselibc//src/ -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/baselibc//src//arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/cmsis-core//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/cmsis-core//include/cmsis-core/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/console/full//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/console/full//include/full/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/mbedtls//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/mbedtls//include/mbedtls/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/os//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/os//include/os/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/testutil//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/testutil//include/testutil/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/tinycrypt//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/tinycrypt//include/tinycrypt/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/util//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/libs/util//include/util/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/net/nimble//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/net/nimble//include/nimble/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/net/nimble/controller//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/net/nimble/controller//include/controller/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/net/nimble/drivers/nrf52//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/net/nimble/drivers/nrf52//include/nrf52/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/net/nimble/host//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/net/nimble/host//include/host/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/net/nimble/host/services/mandatory//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/net/nimble/host/services/mandatory//include/mandatory/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/net/nimble/host/store/ram//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/net/nimble/host/store/ram//include/ram/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/sys/log//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/sys/log//include/log/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/sys/stats//include -I/Users/briangiori/dev/newt/blegpio/repos/apache-mynewt-core/sys/stats//include/stats/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/targets/blegpio//include -I/Users/briangiori/dev/newt/blegpio/targets/blegpio//include/blegpio/arch/cortex_m4 -I/Users/briangiori/dev/newt/blegpio/targets/blegpio//src/ -I/Users/briangiori/dev/newt/blegpio/targets/blegpio//src//arch/cortex_m4