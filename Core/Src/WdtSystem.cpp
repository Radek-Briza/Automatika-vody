

#include "Main.h"
#include "FreeRTOS.h"
//#include "iwdg.h"
#include "task.h"
#include "semphr.h"
#include <cstdio>
#include <atomic>


static std::atomic<uint32_t> gAliveMask{0};
constexpr uint32_t TASK_PUMP_BIT = (1u << 0);
constexpr uint32_t TASK_APP_BIT = (1u << 1);
constexpr uint32_t EXPECTED_MASK = TASK_PUMP_BIT | TASK_APP_BIT;

[[maybe_unused]] 
void WdtSupervisorTask(void*)
{

//MX_IWDG_Init();

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));

        uint32_t snapshot = gAliveMask.exchange(0);


        if (snapshot == EXPECTED_MASK)
        {
            printf("WDT OK\r\n");
           // HAL_IWDG_Refresh( &hiwdg);

        }
        else
        {
            printf("WDT FAIL\r\n");

            BSP_LED_On(LED_RED); 
        }

        gAliveMask = 0;
    }
}
