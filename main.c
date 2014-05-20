
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
	ucAdjCHx=1;//������У��״̬	
	ADJUSTING = 0;//������У��״̬	
	uc_gDriEnyRestNum = 1;//�ϵ�
	SetSystemStatus(&strPowerMode[0]);							//��λ
	
	InitializeVariable(SYSTEM_RESET);
	powerFlag = SYSTEM_RESET;
	while(1)
	{

		if(AC_POWER_ON == GetACPowerStatus())									// �ϵ�
		{
			if(powerFlag!=POWER_ON)
			{
				powerFlag=POWER_ON;
				SetSystemStatus(&strPowerMode[1]);
				InitializeVariable(POWER_ON);

			}	
		}
		else													// ����
		{
			if(powerFlag!=POWER_OFF)
			{
                		SetSystemStatus(&strPowerMode[2]);					// POWER_OFF ģʽ���رմ󹦺���Դ
               		 if(powerFlag==POWER_ON)
		                {
		                    InitializeVariable(POWER_OFF);
		                }
		                InitializeVariable(IDLE_MODE);
		                powerFlag=POWER_OFF;
			}	
		        SetSystemStatus(&strPowerMode[4]);
			//ScanOneConverKey();//�����Ѿ����㣬ɨ��һ�ΰ�����ȷ������״̬
		}


		SysApiRuning();
		if(powerFlag == POWER_ON)
		{
			//����
			// ͨ��
			// ����
			// ����ESAM����
			// ͨ
			CommExplain();
//			GetIVOffset(); 	//�����ڲ�ʵ��2���ӳ�����һ·�Ĺ���
			ManageEnergyMeasure();
            		//ManageRelay();
           		 ClearMeterControl();
			CheckMeterRunStatusWord(0);//д�������״̬��
		}
		//����
		// ʱ�����

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

