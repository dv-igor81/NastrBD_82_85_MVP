#ifndef Shared_Enum_TypesH
#define Shared_Enum_TypesH

// Состояние выполнения задачи
enum TaskExecutionStatus_Tag {
  TaskNotCompleted, // 1. Задача не выполняется
  TaskRunsInLoop, // 2. Задача выполняется в цикле
  PreparingForTaskCompletion }; // 3. Подготовка к завершению задачи
typedef TaskExecutionStatus_Tag TaskExecutionStatus;


#endif
