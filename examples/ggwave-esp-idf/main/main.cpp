/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "ggwave.h"
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"
#include <driver/dac.h>

extern "C"
{
   void app_main(void);
}
TaskHandle_t ggwaveTaskHandler;

void prindHeap()
{
   int spiram_available = heap_caps_get_free_size(MALLOC_CAP_SPIRAM);
   int internal_available = heap_caps_get_free_size(MALLOC_CAP_INTERNAL);
   printf("\nRAM %d, %d", internal_available, spiram_available);
}

void ggwaveTask(void *voidData)
{
   dac_output_enable(DAC_CHANNEL_2);
   
   ggwave_Parameters params = GGWave::getDefaultParameters();
   GGWave *ggwave = new GGWave(params);

   const char *payload = "test";

   GGWave::CBWaveformOut cbWaveformOut = [&](const void *data, uint32_t nBytes) {
      char *p = (char *)data;
      //  std::copy(p, p + nBytes, outputBuffer);

      int nSamples = nBytes / ggwave->getSampleSizeBytesOut();
      printf("\nDONE. Samples %d, length %d", nSamples, nBytes);
      printf("\n  %d", (((uint8_t *)data)[4]));
      for (int i = 0; i < nBytes; i++)
      {

         dac_output_voltage(DAC_CHANNEL_2, p[i]);
         // vTaskDelay(5000 / portTICK_PERIOD_MS);
         pdMS_TO_TICKS(32);
      }
   };

   ggwave->init(payload, 25);
   printf("\nDecode");

   if (ggwave->encode(cbWaveformOut) == false)
   {
      printf("Failed to encode data - GGWave instance \n");
      return;
   }

   printf("\nDone");
   while (true)
   {
   }
   {
      //we can't return, should loop or close the task
      vTaskDelay(5000 / portTICK_PERIOD_MS);
   }
}
void app_main(void)
{
   xTaskCreatePinnedToCore(
       ggwaveTask,
       "ggwave task",
       50000,
       NULL,
       0,
       &ggwaveTaskHandler,
       0);

   while (1)
   {
      printf("\nworking\n");
      vTaskDelay(5000 / portTICK_PERIOD_MS);
   }
}
