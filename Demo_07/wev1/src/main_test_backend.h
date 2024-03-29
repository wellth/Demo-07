
#if 1
#define IN_TEXT_FILE           "./Demon/MDB/in.txt"
#define IN_BP_FILE				"./Demon/MDB/abort.txt"
#define IN_ENTERY_FILE         "./Demon/MDB/Inpt.csv"
#define OT_TEXT_FILE           "./Demon/MDB/out.txt"
#define OT_ENTERY_FILE         "./Demon/MDB/Data.csv"

//************Summary files*************
#define LOGIN_SUMMARY_FILE		"./Demon/MDB/login_sum.csv"
#define BMI_SUMMARY_FILE		"./Demon/MDB/bmi_sum.csv"
#define BP_SUMMARY_FILE			"./Demon/MDB/bp_sum.csv"
#define BF_SUMMARY_FILE			"./Demon/MDB/bf_sum.csv"
#define CO_SUMMARY_FILE			"./Demon/MDB/co_sum.csv"
#define SMS_SEND_FILE			"./Demon/MDB/SMS.txt"
//************Summary files*************
#endif
#if 0
#define IN_TEXT_FILE           "./Sensor123/MDB/in.txt"
#define IN_ENTERY_FILE         "./Sensor123/MDB/Inpt.csv"
#define OT_TEXT_FILE           "./Sensor123/MDB/out.txt"
#define OT_ENTERY_FILE         "./Sensor123/MDB/Data.csv"
#endif
#define BkGndImage             "src/Images/Home.jpg"

#define WEIGHT_TIMEOUT		30
#define BODYFAT_TIMEOUT		30
#define SMOKE_TIMEOUT		60
#define BP_TIMEOUT			150
#define ECG_TIMEOUT			40


/**************************************************************************************
 * blood pressure declarations
 **************************************************************************************/

typedef struct{
	char InBuf[10];
}_BP_IN_FILE;

typedef struct{
	char SysP[10];
	char Comma1;
	char DiaP[10];
	char Comma2;
	char PulseRate[10];
        char Comma3;
        char ErrorCode[4];
}_BP_TEST;

void GoToBpScreen(void);
void QuitBpWindow(void);
void GetBpOutput(void);
void StartBpTest( GtkWidget *widget, gpointer data);

/**************************************************************************************
 * common
 **************************************************************************************/

extern void DrawScreen1(void);
extern void ClearOutPutFile(void);
extern void ReadBMIForSummary();
extern void ReadBPForSummary ();
extern void ReadBFForSummary ();

extern volatile char StartTimer;


typedef struct{
	char Login_name[64]; 
	int Age;
	char Gender[8];
	float Weight;
	float BMI_val;
	float Height;
	float BF_val;
	float CO_val;
	float SysBP;
	float DiaBp;
	float PulseRate;
}_USER_SUMMARY_DATA;
extern _USER_SUMMARY_DATA UserSummaryData;
/**************************************************************************************
 * common
 **************************************************************************************/

/**************************************************************************************
 * body fat declarations
 **************************************************************************************/

typedef struct{
	char InBuf[10];
}_BLI_IN_FILE;

typedef struct{
	char BliValue[10];
}_BLI_TEST;

typedef struct{
	char Weight[10];
	char Comma;
	char Hight[10];
	char Comma2;
	char Gender[10];
	char Comma3;
	char Age[10];
}_BLI_INPUT_DATA;


void GetBliOutput(void);
void GoToBliScreen(void);
void QuitBliwindow(void);
void GetWindowEntry(void);
void StartBliTest( GtkWidget *widget, gpointer data);
extern void test_home_btnclicked(GtkWidget *widget, gpointer user_data);

extern volatile int test_timeout;

void TimerInit(void);
extern volatile int wait_for_5sec;
void send_bf_measure_request();

/**************************************************************************************
 * weight and BMI test declarations
 **************************************************************************************/

typedef struct{
	char InBuf[10];
}_WT_IN_FILE;

typedef struct{
	char Weight[10];
	char Comma;
	char BmiValue[10];
}_BMI_TEST;

typedef struct{
	char Weight[10];
	char Comma;
	char Hight[10];
}_WT_INPUT_DATA;


void GoToBmiScreen(void);
void QuitBmiWindow(void);
extern void DrawScreen1(void);
void StartBmiTest( GtkWidget *widget, gpointer data );

void WriteEntryFile(void);
void GetBmiOutput(void);
void ClearOutPutFile(void);

/**************************************************************************************
 * CO test declarations
 **************************************************************************************/
void GetCoOutput();
void smoke_test_wait_start();
void bp_test_wait_start();
