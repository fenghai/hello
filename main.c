
#include "sh79f7010e.h"
#include "Platform\Inc\Api.h"
#include "Application\Inc\Ap.h"


code STR_POWER_MODE_PARA strPowerMode[] =
{
	SYSTEM_RESET,PAX_OFF,PAX_OFF,PAX_OFF,PAX_OFF,
	POWER_ON,PAX_OFF,PAX_OFF,PAX_ON,PAX_OFF,
	POWER_OFF,PAX_OFF,PAX_ON,PAX_ON,PAX_OFF,  
	WAIT_MODE,PAX_OFF,PAX_OFF,PAX_ON,PAX_OFF,
	IDLE_MODE,PAX_OFF,PAX_OFF,PAX_ON,PAX_OFF,
};



void main(void)
{
	SP=0x80;
	PSW=0x00;
	ucAdjCHx=1;//不处于校表状态	
	ADJUSTING = 0;//不处于校表状态	
	uc_gDriEnyRestNum = 1;//上电
	SetSystemStatus(&strPowerMode[0]);							//复位
	
	InitializeVariable(SYSTEM_RESET);
	powerFlag = SYSTEM_RESET;
	while(1)
	{

		if(AC_POWER_ON == GetACPowerStatus())									// 上电
		{
			if(powerFlag!=POWER_ON)
			{
				powerFlag=POWER_ON;
				SetSystemStatus(&strPowerMode[1]);
				InitializeVariable(POWER_ON);

			}	
		}
		else													// 掉电
		{
			if(powerFlag!=POWER_OFF)
			{
                		SetSystemStatus(&strPowerMode[2]);					// POWER_OFF 模式，关闭大功耗资源
               		 if(powerFlag==POWER_ON)
		                {
		                    InitializeVariable(POWER_OFF);
		                }
		                InitializeVariable(IDLE_MODE);
		                powerFlag=POWER_OFF;
			}	
		        SetSystemStatus(&strPowerMode[4]);
			//ScanOneConverKey();//按键已经清零，扫描一次按键，确定按键状态
		}


		SysApiRuning();
		if(powerFlag == POWER_ON)
		{
			//任务
			// 通信
			// 计量
			// 控制ESAM操作
			// 通
			CommExplain();
//			GetIVOffset(); 	//函数内部实现2秒钟出来另一路的功率
			ManageEnergyMeasure();
            		//ManageRelay();
           		 ClearMeterControl();
			CheckMeterRunStatusWord(0);//写电表运行状态字
		}
		//任务
		// 时间管理

		SoftTimer();
 		TimeEvent();
		MamageEvent();
        Display();




		#if 0
		if(powerFlag == POWER_ON)
		{
	 		SetSystemStatus(&strPowerMode[3]);  
		}
		#endif
				 
	}
}

