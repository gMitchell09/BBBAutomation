float ReadTemp();
void AddSchedule(float, time_t, time_t);
void RemoveSchedule(time_t, time_t);
bool ShouldRunHeat(time_t, time_t);
bool ShouldRunAC(time_t, time_t);
float TargetTemp(time_t);
void EnableFan();
void DisableFan();
std::string PrintSchedule();

/*
 * Transformed into:
 * enum API_CALL { FuncName1, FuncName2, ... };
 * const std::string API_CALLS[] = { "FuncName1", "FuncName2", ... };
*/

