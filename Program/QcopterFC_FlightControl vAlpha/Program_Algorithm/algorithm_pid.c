/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "module_sensor.h"
#include "algorithm_pid.h"
#include "algorithm_mathUnit.h"
#include "algorithm_quaternion.h"
/*=====================================================================================================*/
/*=====================================================================================================*
**��� : PID_Init
**�\�� : PID Initialize
**��J : PID
**��X : None
**�ϥ� : PID_Init(&PID)
**=====================================================================================================*/
/*=====================================================================================================*/
void PID_Init( PID_Struct *PID )
{
	PID->Kp      = 2.5f;
	PID->Ki      = 0.0f;
	PID->Kd      = 0.45f;

	PID->Err0    = 0.0f;
	PID->Err1    = 0.0f;
	PID->Err2    = 0.0f;
	PID->SumErr  = 0.0f;
	PID->ZeroErr = 0.0f;
	PID->Output  = 0.0f;
	PID->KiMax   = 400.0f;
	PID->KiMin   = -400.0f;
	PID->OutMax  = 800.0f;
	PID->OutMin  = -800.0f;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**��� : PID_IncCal
**�\�� : Calculate Incremental PID
**��J : PID, CurrentVal
**��X : None
**�ϥ� : PID_IncCal(&PID, CurrentVal)
**=====================================================================================================*/
/*=====================================================================================================*/
float PID_IncCal( PID_Struct *PID, float CurrentVal )
{
	float Value_Kp;	// ���
	float Value_Ki;	// �n��
	float Value_Kd;	// �L��

	PID->Err0 = PID->Err1;
	PID->Err1 = PID->Err2;
	PID->Err2 = CurrentVal - PID->ZeroErr;

	Value_Kp    = PID->Kp*(PID->Err2 - PID->Err1);
	Value_Ki    = PID->Ki*PID->Err2;
	Value_Kd    = PID->Kd*(PID->Err2 - 2.0f*PID->Err1 + PID->Err0);
	PID->Output = Value_Kp + Value_Ki + Value_Kd;

	if(PID->Output>PID->OutMax)
		PID->Output = PID->OutMax;
	if(PID->Output<PID->OutMin)
		PID->Output = PID->OutMin;

	return (PID->Output);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**��� : PID_IncCal
**�\�� : Calculate Positional PID
**��J : PID, CurrentVal
**��X : None
**�ϥ� : PID_PosCal(&PID, CurrentVal)
**=====================================================================================================*/
/*=====================================================================================================*/
float PID_PosCal( PID_Struct *PID, float CurrentVal )
{
	float Value_Kp;	// ���
	float Value_Ki;	// �n��
	float Value_Kd;	// �L��

	PID->Err1 = PID->Err2;
	PID->Err2 = CurrentVal - PID->ZeroErr;

	PID->SumErr += PID->Err2;

	Value_Kp = PID->Kp*PID->Err2;
	Value_Ki = PID->Ki*PID->SumErr;
	Value_Kd = PID->Kd*(PID->Err2 - PID->Err1);

	if(Value_Ki>PID->KiMax) {
		PID->SumErr -= PID->Err2;
		Value_Ki = PID->KiMax;
	}
	if(Value_Ki<PID->KiMin) {
		PID->SumErr -= PID->Err2;
		Value_Ki = PID->KiMin;
	}

	PID->Output = Value_Kp + Value_Ki + Value_Kd;

	if(PID->Output>PID->OutMax)
		PID->Output = PID->OutMax;
	if(PID->Output<PID->OutMin)
		PID->Output = PID->OutMin;

	return (PID->Output);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**��� : PID_IncCal
**�\�� : Calculate Positional PID
**��J : PID, CurrentVal
**��X : None
**�ϥ� : PID_PosCal(&PID, CurrentVal)
**=====================================================================================================*/
/*=====================================================================================================*/
float PID_AHRS_Cal( PID_Struct *PID, float Angle, float Gyroscope )
{
	float Value_Kp;	// ���
	float Value_Ki;	// �n��
	float Value_Kd;	// �L��

	PID->Err1 = PID->ZeroErr - Angle;

//   if(Angle>-0.1f && Angle<0.1f)
//     PID->SumErr = 0.0f;
  PID->SumErr = PID->SumErr + PID->Err1;

	Value_Kp = PID->Kp*PID->Err1;
	Value_Ki = PID->Ki*PID->SumErr;
	Value_Kd = PID->Kd*Gyroscope;

	if(Value_Ki>PID->KiMax)
		Value_Ki = PID->KiMax;
	if(Value_Ki<PID->KiMin)
		Value_Ki = PID->KiMin;

	PID->Output = Value_Kp + Value_Ki - Value_Kd;

	if(PID->Output>PID->OutMax)
		PID->Output = PID->OutMax;
	if(PID->Output<PID->OutMin)
		PID->Output = PID->OutMin;

	return (-PID->Output);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
