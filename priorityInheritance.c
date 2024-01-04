---------- Tasks ----------------
// lowest prio, no initial blocking, functionality at every 7 mS
void task1 (void *tmp)
{
	while (1) {
		xSemaphoreTake(mySem, portMAX_DELAY);
		HAL_Delay(7);
		xSemaphoreGive(mySem);
	}
}

// Middle prio task, initial block time of 2 mS
void task2 (void *tmp)
{
	vTaskDelay(pdMS_TO_TICKS(2));
	while (1) {
		HAL_Delay(2);
	}
}

// Higher prio task, initial block time of 5 mS
void task3 (void *tmp)
{
	vTaskDelay(pdMS_TO_TICKS(4));
	while (1) {
		xSemaphoreTake(mySem, portMAX_DELAY);
		HAL_Delay(5);
		xSemaphoreGive(mySem);
	}
}

---------- Inside Main -----------
xTaskCreate(task1, "low", 200, NULL, 1, NULL);
xTaskCreate(task2, "mid", 200, NULL, 2, NULL);
xTaskCreate(task3, "high", 200, NULL, 3, NULL);
vTaskStartScheduler();
