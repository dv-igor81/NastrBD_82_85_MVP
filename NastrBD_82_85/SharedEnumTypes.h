#ifndef Shared_Enum_TypesH
#define Shared_Enum_TypesH

// ��������� ���������� ������
enum TaskExecutionStatus_Tag {
  TaskNotCompleted, // 1. ������ �� �����������
  TaskRunsInLoop, // 2. ������ ����������� � �����
  PreparingForTaskCompletion }; // 3. ���������� � ���������� ������
typedef TaskExecutionStatus_Tag TaskExecutionStatus;


#endif
