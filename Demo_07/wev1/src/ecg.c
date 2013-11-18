#include <config.h>
#include <gtk/gtk.h>

#include <glib/gi18n.h>
#include <string.h>
#include "window_defs_n_config.h"
#include "main_test_backend.h"

/*****************************************************************************************************************
                                                        Variable Declaration
******************************************************************************************************************/
_BP_IN_FILE Indata2;
_BP_TEST Bp;

GtkWidget *t5_label_sys_msg, *t5_label_timer_label;
static GtkWidget *t5_button1, *t5_button2, *t5_button3, *t5_button4, *t5_button5, *t5_home_button, *t5_check;
static GtkWidget *t5b_button1, *t5b_button5, *t5b_home_button;

unsigned char ECGTestEn = 0;
unsigned char ECGCheckEn = 0;
extern GtkWidget *window,*Bliwindow,*Bpwindow,*Bmiwindow;

static int init_test5_window = 0, init_test5_b_window = 0;
GtkBuilder *Test5Builder, *Test5bBuilder;
/**************************Variable Declaration******************************/


/*****************************************************************************************************************
                                                       Button click message handler
******************************************************************************************************************/
void test5_home_btnclicked(GtkWidget *widget, gpointer user_data)
{
	hide_window_test5();
	show_window_home();
	start_timer = 0;
}

void test5_button_set_state(int bool_val){
	gtk_widget_set_sensitive(t5_button1, bool_val);
	if(bool_val == FALSE)
		disable_test5_repeate();
	
	gtk_widget_set_sensitive(t5_button3, bool_val);
	gtk_widget_set_sensitive(t5_button4, bool_val);
	gtk_widget_set_sensitive(t5_button5, bool_val);

	GtkWidget *feed_back;
	if(bool_val == TRUE){
		feed_back = GTK_WIDGET (gtk_builder_get_object (Test5Builder, "label9"));
		//gtk_label_set_label (feed_back, "Please wait upto sensor is ready");
		gtk_label_set_label (feed_back, "Click to measure");
	}
}

void enable_test5_repeate(){
	GtkWidget *feed_back;
	gtk_widget_set_sensitive(t5_button3, TRUE);
	gtk_widget_set_sensitive(t5_button4, TRUE);
	feed_back = GTK_WIDGET (gtk_builder_get_object (Test5Builder, "label9"));
	gtk_label_set_label (feed_back, "Click to measure");
}
void disable_test5_repeate(){
	GtkWidget *feed_back;
	gtk_widget_set_sensitive(t5_button3, FALSE);
	gtk_widget_set_sensitive(t5_button4, FALSE);
	//feed_back = GTK_WIDGET (gtk_builder_get_object (Test3Builder, "label9"));
	//gtk_label_set_label (feed_back, "Click to measure");
}

void reset_test5_results() {
	gtk_label_set_label (t5_label_timer_label, "0 M: 0 S");
//	gtk_label_set_label (t5_label_sys_msg, "System message");

}
void test5_b_next_btnclicked (GtkWidget *widget, gpointer user_data) {
	reset_test5_results();
	hide_window_test5_b();
	//show_window_test1();
	//show_window_qna();
	show_window_health_summary();
}

void test5_next_btnclicked(GtkWidget *widget, gpointer user_data) {
	reset_test5_results();
	hide_window_test5();
	show_window_test5_b();

//	if(isQuickWellthCheck)
//		test4_hide_next_button_n_image();
	//show_window_test1();
	//show_window_qna();
	//show_window_user_summary();
	start_timer = 0;
	ECGTestEn = 0;
	//printf("---------------------completed---------------");
	//set_cur_test = CUR_TEST2;
	//show_measure_btn_hide_repeate_btn();
}


void test5_click_to_measure_btnclicked(GtkWidget *widget, gpointer user_data)
{
	FILE *fp;
	long int Delay = 0xFFFFFFFF;
	//start_timer = 1;
	GtkWidget *feed_back;
	reset_test5_results();
	
	feed_back = GTK_WIDGET (gtk_builder_get_object (Test5Builder, "label9"));
	gtk_label_set_label (feed_back, "Please wait..! Getting your ECG");

	
	fp = fopen (IN_TEXT_FILE , "w");
	if(fp<0){
		printf(" System is not able to create file \n");
	}
	else{
		printf("ip is ready \n");
		ClearOutPutFile();
		strcpy(Indata2.InBuf,"EcgTest");
		fwrite(&Indata2,sizeof(Indata2),1,fp);
		printf(" File has been Updated \n");
		fclose(fp);		
		ECGTestEn=1;	
	}
	/*
	while(BPTestEn==1){
		while(Delay>0){
			Delay--;
		}
		GetBpOutput();
		Delay = 0xFFFFFFFF;
	}
*/
	test5_button_set_state(FALSE);
	Minutes = 0;
	Seconds = 0;
	ECGTestEn=1;	
	StartTimer = 1;
	test_timeout = ECG_TIMEOUT;
/***
	t4_button1 = GTK_WIDGET (gtk_builder_get_object (Test4Builder, "exit"));
	gtk_widget_set_sensitive(t4_button1, FALSE);
	t4_button5 = GTK_WIDGET (gtk_builder_get_object (Test4Builder, "next"));
	gtk_widget_set_sensitive(t4_button5, FALSE);
	sleep(3);
****/
	TimerInit();
	return;
}

void test5_check_btnclicked(GtkWidget *widget, gpointer user_data)
{
	FILE *fp;
	long int Delay = 0xFFFFFFFF;
	//start_timer = 1;
	GtkWidget *feed_back;
	reset_test5_results();
	
	feed_back = GTK_WIDGET (gtk_builder_get_object (Test5Builder, "label9"));
	gtk_label_set_label (feed_back, "Please wait..! Checking Connection ");

	
	fp = fopen (IN_TEXT_FILE , "w");
	if(fp<0){
		printf(" System is not able to create file \n");
	}
	else{
		printf("ip is ready \n");
		ClearOutPutFile();
		strcpy(Indata2.InBuf,"EcgCheck");
		fwrite(&Indata2,sizeof(Indata2),1,fp);
		printf(" File has been Updated \n");
		fclose(fp);		
		ECGCheckEn=1;	
	}
	/*
	while(BPTestEn==1){
		while(Delay>0){
			Delay--;
		}
		GetBpOutput();
		Delay = 0xFFFFFFFF;
	}
*/
	test5_button_set_state(FALSE);
	Minutes = 0;
	Seconds = 0;
	ECGCheckEn=1;	
	StartTimer = 1;
	test_timeout = ECG_TIMEOUT;
/***
	t4_button1 = GTK_WIDGET (gtk_builder_get_object (Test4Builder, "exit"));
	gtk_widget_set_sensitive(t4_button1, FALSE);
	t4_button5 = GTK_WIDGET (gtk_builder_get_object (Test4Builder, "next"));
	gtk_widget_set_sensitive(t4_button5, FALSE);
	sleep(3);
****/
	TimerInit();
	return;
}

void test5_hide_next_button_n_image(){
	GtkWidget *button;GtkImage *nextImage;
	button = GTK_WIDGET (gtk_builder_get_object (Test5bBuilder, "next"));
	nextImage = GTK_WIDGET (gtk_builder_get_object (Test5bBuilder, "image3"));
	gtk_widget_hide(button);
	gtk_widget_hide(nextImage);
}
/***********************Button click message handler**********************************************************************/

static GtkWidget*
create_test5_window (void)
{
	GtkWidget *window; 
	GtkImage *imageClient, *imageWellth, *imageTest, *imageBG, *imageTestStat;

	GError** error = NULL;
	

	/* Load UI from file */

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (Test5Builder, NULL);

	/* Get the window object from the ui file */
	window = GTK_WIDGET (gtk_builder_get_object (Test5Builder, TEST5_WINDOW));
        if (!window)
        {
                g_critical ("Widget \"%s\" is missing in file %s.",
				TEST5_WINDOW,
				TEST5_UI_FILE);
        }

	GdkPixbufAnimation * pixbufclntanm = gdk_pixbuf_animation_new_from_file(CLIENT_LOGO, error);
	GdkPixbufAnimation * pixbufwlthanm = gdk_pixbuf_animation_new_from_file(WELLTH_LOGO, error);
	imageClient = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test5Builder, "clnt_logo"));
	imageWellth = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test5Builder, "wellth_logo"));
	gtk_image_set_from_animation(GTK_IMAGE(imageClient), pixbufclntanm);
	gtk_image_set_from_animation (GTK_IMAGE(imageWellth), pixbufwlthanm);

	GdkPixbufAnimation * pixbufBGanm = gdk_pixbuf_animation_new_from_file(BG, error);
	imageBG = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test5Builder, "image1"));
	gtk_image_set_from_animation(GTK_IMAGE(imageBG), pixbufBGanm);

	GdkPixbufAnimation * pixbufTestanm = gdk_pixbuf_animation_new_from_file(TEST5, error);
	imageTest = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test5Builder, "image2"));
	gtk_image_set_from_animation(GTK_IMAGE(imageTest), pixbufTestanm);

	
/******
	GdkPixbufAnimation * pixbufaddanm = gdk_pixbuf_animation_new_from_file(ADDS2, error);
	GtkImage *adds = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test4Builder, "adds"));
	gtk_image_set_from_animation(GTK_IMAGE(adds), pixbufaddanm);
	
	GdkPixbufAnimation * pixbuf1 = gdk_pixbuf_animation_new_from_file(GRAPH, error);
	//GtkImage * grf = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test4Builder, "graph"));
	//gtk_image_set_from_animation(GTK_IMAGE(grf), pixbuf1);
******/
	
	t5_button1 = GTK_WIDGET (gtk_builder_get_object (Test5Builder, "exit"));
 	 g_signal_connect (G_OBJECT (t5_button1), "clicked",
                    G_CALLBACK (test_exit_btnclicked),
                    NULL);

	profileBtnClickedFrom = test5_pro_btn;
	t5_button2 = GTK_WIDGET (gtk_builder_get_object (Test5Builder, "profile"));
 	 g_signal_connect (G_OBJECT (t5_button2), "clicked",
                    G_CALLBACK (test_profile_btnclicked),
                    profileBtnClickedFrom);

	t5_button4 = GTK_WIDGET (gtk_builder_get_object (Test5Builder, "repeate"));
	g_signal_connect (G_OBJECT (t5_button4), "clicked",
                    G_CALLBACK (test5_click_to_measure_btnclicked),
                    NULL);
	
	t5_check = GTK_WIDGET (gtk_builder_get_object (Test5Builder, "check"));
	g_signal_connect (G_OBJECT (t5_check), "clicked",
                    G_CALLBACK (test5_check_btnclicked),
                    NULL);
	
	GtkWidget *timer_label = GTK_WIDGET (gtk_builder_get_object (Test5Builder, "timer_label"));
	t5_button3 = GTK_WIDGET (gtk_builder_get_object (Test5Builder, "click_to_measure"));
 	 g_signal_connect (G_OBJECT (t5_button3), "clicked",
                    G_CALLBACK (test5_click_to_measure_btnclicked),
                    NULL);
	
	continue_timer = TRUE;
    start_timer = TRUE;
	//g_signal_connect(G_OBJECT(t4_button3), "clicked", G_CALLBACK(_start_timer), timer_label);
	//g_signal_connect(G_OBJECT(t4_button31), "clicked", G_CALLBACK(_start_timer), timer_label);

	t5_label_timer_label = GTK_WIDGET (gtk_builder_get_object (Test5Builder, "timer_label"));
	//t5_label_sys_msg = GTK_WIDGET (gtk_builder_get_object (Test4Builder, "label6"));

	t5_button5 = GTK_WIDGET (gtk_builder_get_object (Test5Builder, "next"));
 	 g_signal_connect (G_OBJECT (t5_button5), "clicked",
                    G_CALLBACK (test5_next_btnclicked),
                    NULL);
	/* 
 	 g_signal_connect (G_OBJECT (t4_button5), "clicked",
                    G_CALLBACK (test4_home_btnclicked),
                    NULL);
	*/
	
	priv = g_malloc (sizeof (struct _Private));
	/* ANJUTA: Widgets initialization for WindowMain.ui - DO NOT REMOVE */

	//g_object_unref (InitialBuilder);
	
	return window;
}

void show_window_test5()
{
	GtkWidget *window, *label;
	GtkWidget *feed_back;
	char lbl_buf[64];
	if(!init_test5_window) {
		   GError *error=NULL;
		Test5Builder = gtk_builder_new ();
		if (!gtk_builder_add_from_file (Test5Builder, TEST5_UI_FILE, &error))
		{
		  g_critical ("Couldn't load builder file: %s", error->message);
		  g_error_free (error);
		}
		create_test5_window();
		init_test5_window = 1;
	}
	label = GTK_WIDGET (gtk_builder_get_object (Test5Builder, "user_name"));
	strcpy(lbl_buf, "Hi ");
	strcat(lbl_buf, GlobalUserName);
	gtk_label_set_label (label, lbl_buf);
	
	// Copy Blank Plot
	system("cp plot/blankplot.png plot/ecgplot.png");
	system("cp plot/blankplot.png plot/ecgprint.png");

	window = GTK_WIDGET (gtk_builder_get_object (Test5Builder, TEST5_WINDOW));
	reset_test5_results();
	feed_back = GTK_WIDGET (gtk_builder_get_object (Test5Builder, "label9"));
	gtk_label_set_label (feed_back, "Click to Measure ");
	gtk_widget_show_all(window);
	cur_active_screen = test5_scrn;
}

void hide_window_test5()
{
	GtkWidget *window;
	window = GTK_WIDGET (gtk_builder_get_object (Test5Builder, TEST5_WINDOW));
	gtk_widget_hide(window);
}

static GtkWidget*
create_test5_b_window (void)
{
	GtkWidget *window; 
	GtkImage *imageClient, *imageWellth, *imageTest, *imageBG, *add;
	GtkWidget *timer_label;

	GtkWidget *vbox1;
	GError** error = NULL;
	int i=0;
	char buf[8];
	

	/* Load UI from file */

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (Test5bBuilder, NULL);

	/* Get the window object from the ui file */
	window = GTK_WIDGET (gtk_builder_get_object (Test5bBuilder, TEST5_b_WINDOW));
        if (!window)
        {
                g_critical ("Widget \"%s\" is missing in file %s.",
				TEST5_b_WINDOW,
				TEST5B_UI_FILE);
        }
/*
	GdkPixbufAnimation * pixbufclntanm = gdk_pixbuf_animation_new_from_file(CLIENT_LOGO, error);
	GdkPixbufAnimation * pixbufwlthanm = gdk_pixbuf_animation_new_from_file(WELLTH_LOGO, error);
	imageClient = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test1Builder, "clnt_logo"));
	imageWellth = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test1Builder, "wellth_logo"));
	gtk_image_set_from_animation(GTK_IMAGE(imageClient), pixbufclntanm);
	gtk_image_set_from_animation (GTK_IMAGE(imageWellth), pixbufwlthanm);
*/
	//GdkPixbufAnimation * pixbufBGanm = gdk_pixbuf_animation_new_from_file(BG, error);
	imageBG = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test5bBuilder, "image1"));
	gtk_image_set_from_animation(GTK_IMAGE(imageBG), pixbufBGanm);
/*
	GdkPixbufAnimation * pixbufTestanm = gdk_pixbuf_animation_new_from_file(TEST1, error);
	imageTest = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test4bBuilder, "image2"));
	gtk_image_set_from_animation(GTK_IMAGE(imageTest), pixbufTestanm);
*/
	

	GdkPixbufAnimation * pixbufaddanm = gdk_pixbuf_animation_new_from_file(ECG1, error);
	add = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test5bBuilder, "adds"));
	gtk_image_set_from_animation(GTK_IMAGE(add), pixbufaddanm);

	
//#endif
	
	//GdkPixbufAnimation * pixbuf1 = gdk_pixbuf_animation_new_from_file(GRAPH, error);
	//GtkImage * grf = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test1Builder, "graph"));
	//gtk_image_set_from_animation(GTK_IMAGE(grf), pixbuf1);

/*
	GdkPixbufAnimation * pixbufStat1anm = gdk_pixbuf_animation_new_from_file(QNA_ICON, error);
	GtkImage* imageTestStat = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test4bBuilder, "next_icon"));
	gtk_image_set_from_animation(GTK_IMAGE(imageTestStat), pixbufStat1anm);
*/
	/*
	GdkPixbufAnimation * pixbuf2 = gdk_pixbuf_animation_new_from_file(T_NEXT_ICON, error);
	GtkImage * nxt_icon = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test4bBuilder, "next_icon"));
	gtk_image_set_from_animation(GTK_IMAGE(nxt_icon), pixbuf2);
	*/
	t5b_button1 = GTK_WIDGET (gtk_builder_get_object (Test5bBuilder, "exit"));
 	 g_signal_connect (G_OBJECT (t5b_button1), "clicked",
                    G_CALLBACK (test_exit_btnclicked),
                    NULL);

	t5b_home_button = GTK_WIDGET (gtk_builder_get_object (Test5bBuilder, "home"));
 	 g_signal_connect (G_OBJECT (t5b_home_button), "clicked",
                    G_CALLBACK (test_home_btnclicked),
                    NULL);
	
	t5b_button5 = GTK_WIDGET (gtk_builder_get_object (Test5bBuilder, "next"));
 	 g_signal_connect (G_OBJECT (t5b_button5), "clicked",
                    G_CALLBACK (test5_b_next_btnclicked),
                    NULL);

	
	
	priv = g_malloc (sizeof (struct _Private));
	/* ANJUTA: Widgets initialization for WindowMain.ui - DO NOT REMOVE */

	//g_object_unref (InitialBuilder);
	
	return window;
}

void show_window_test5_b()
{
	GtkWidget *window, *label;
	GtkWidget *f_username, *f_date, *f_datelabel;
	GtkWidget *f_age, *f_gender, *f_hrlabel, *f_hr;
	GtkImage  *add;
	char lbl_buf[64];
	char f_buf[64];
	GError** error = NULL;

	if(!init_test5_b_window) {
		   GError *error=NULL;
		Test5bBuilder = gtk_builder_new ();
		if (!gtk_builder_add_from_file (Test5bBuilder, TEST5B_UI_FILE, &error))
		{
		  g_critical ("Couldn't load builder file: %s", error->message);
		  g_error_free (error);
		}
		create_test5_b_window();
		init_test5_b_window = 1;
	}
	label = GTK_WIDGET (gtk_builder_get_object (Test5bBuilder, "user_name"));
	strcpy(lbl_buf, "Hi ");
	strcat(lbl_buf, GlobalUserName);
	gtk_label_set_label (label, lbl_buf);

	f_username = GTK_WIDGET (gtk_builder_get_object (Test5bBuilder, "label4"));
	gtk_label_set_label (f_username,UserSummaryData.Login_name );

	f_date = GTK_WIDGET (gtk_builder_get_object (Test5bBuilder, "label6"));
	gtk_label_set_label (f_date," " );

	f_datelabel = GTK_WIDGET (gtk_builder_get_object (Test5bBuilder, "label5"));
	gtk_label_set_label (f_datelabel," " );

	f_age = GTK_WIDGET (gtk_builder_get_object (Test5bBuilder, "label8"));
	sprintf(f_buf,"%d",UserSummaryData.Age);
	gtk_label_set_label (f_age,f_buf );

	f_gender = GTK_WIDGET (gtk_builder_get_object (Test5bBuilder, "label10"));
	gtk_label_set_label (f_gender,UserSummaryData.Gender );
	printf("Gender - %s \n",UserSummaryData.Gender);

	f_hrlabel = GTK_WIDGET (gtk_builder_get_object (Test5bBuilder, "label11"));
	gtk_label_set_label (f_hrlabel," " );

	f_hr = GTK_WIDGET (gtk_builder_get_object (Test5bBuilder, "label12"));
	gtk_label_set_label (f_hr," " );

	GdkPixbufAnimation * pixbufaddanm = gdk_pixbuf_animation_new_from_file(ECG1, error);
	add = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (Test5bBuilder, "adds"));
	gtk_image_set_from_animation(GTK_IMAGE(add), pixbufaddanm);

	
	window = GTK_WIDGET (gtk_builder_get_object (Test5bBuilder, TEST5_b_WINDOW));
	gtk_widget_show_all(window);
	cur_active_screen = test5_b_scrn;
	if(isQuickWellthCheck)
		gtk_widget_hide(t5b_button1);
	else
		gtk_widget_hide(t5b_home_button);
}

void hide_window_test5_b()
{
	GtkWidget *window;
	window = GTK_WIDGET (gtk_builder_get_object (Test5bBuilder, TEST5_b_WINDOW));
	gtk_widget_hide(window);
}

void CheckEcgOutput(void){
	GtkWidget *window;
	GtkWidget *feed_back;
	FILE *fp;
	char Buf[2];
	char buf1[40], buf2[40], buf3[40];
	char BP_test_msg[128];
	struct timeval tv;
	
	if(ECGCheckEn==1){
		fp = fopen (OT_TEXT_FILE, "r+");
		if(fp<0){
			printf(" System is not able to create file \n");
		}
		else{
			fread(&Buf,1,1,fp);
			fclose(fp);	
			
			if(Buf[0] == '1')
			{
				printf("Check the output\n");
				printf(" String info %d \n",Buf[0]);
				printf("System Got Data Updated \n");

				fp = fopen (OT_ENTERY_FILE, "r");
				fread(&buf1,1,1,fp);
				fclose(fp);

				ECGCheckEn=0;
				Minutes = 0;
				Seconds = 0;
				ClearOutPutFile();
				
				test5_button_set_state(TRUE);

				feed_back = GTK_WIDGET (gtk_builder_get_object (Test5Builder, "label9"));
				if (buf1[0] == '1')
					gtk_label_set_label (feed_back, "ECG Working .. Please Click MEASURE to Start ");
				else
					gtk_label_set_label (feed_back, "ECG Not Working .. Please Skip the test ");
				
				window = GTK_WIDGET (gtk_builder_get_object (Test5Builder, TEST5_WINDOW));
				set_cur_test = CUR_TEST5;
				show_measure_btn_hide_repeate_btn();
				gtk_widget_show_all(window);
				if(isQuickWellthCheck)
					test5_hide_next_button_n_image();
			}			
		}
	}
}


void GetEcgOutput(void){
	GtkWidget *window;
	GtkWidget *feed_back;
	FILE *fp;
	char Buf[2];
	char buf1[40], buf2[40], buf3[40];
	char BP_test_msg[128];
	struct timeval tv;
	
	if(ECGTestEn==1){
		fp = fopen (OT_TEXT_FILE, "r+");
		if(fp<0){
			printf(" System is not able to create file \n");
		}
		else{
			fread(&Buf,1,1,fp);
			fclose(fp);	
			
			if(Buf[0] == '1')
			{
				printf("Check the output\n");
				printf(" String info %d \n",Buf[0]);
				printf("System Got Data Updated \n");
/*
				fp = fopen (OT_ENTERY_FILE, "r");
				fread(&Bp,sizeof(Bp),1,fp);
				fclose(fp);
				printf("BP Systolic BP  is %d\n",Bp.SysP[0]);
				printf("BP Diastolic BP is %d\n",Bp.DiaP[0]);
    			printf("BP Pulse Rate  is %d\n",Bp.PulseRate[0]);

				sprintf(buf1, "%s mmHg", &Bp.SysP);
				sprintf(buf2, "%s mmHg", &Bp.DiaP);
				sprintf(buf3, "%s", &Bp.PulseRate);

                                gettimeofday( &tv,NULL);
                                printf(" GetBpOutput : Time - %d - \n",tv.tv_sec);

				gtk_label_set_label (label_sys_bp, buf1);
				gtk_label_set_label (label_dia_bp, buf2);
				gtk_label_set_label (label_pulse_rate, buf3);
*/
				ECGTestEn=0;
				Minutes = 0;
				Seconds = 0;
				ClearOutPutFile();
				
/*
				ReadBPForSummary ();
				g_print("reading message-----\n");
				//UserSummaryData.SysBP = 140.0;
				//UserSummaryData.DiaBp = 90.0;
				blood_pressure_system_msg(UserSummaryData.SysBP, UserSummaryData.DiaBp, UserSummaryData.PulseRate, BP_test_msg);
				if( strcmp(BP_test_msg, "Normal") == 0 ){
					gtk_widget_show (t4_result_smsg1);
					gtk_widget_show (t4_result_smsg5);
					gtk_widget_hide (t4_normal_smsg1);					
					gtk_widget_hide (t4_normal_smsg5);
				}
				if( strcmp(BP_test_msg, "Pre-hypertension") == 0 ){
					gtk_widget_show (t4_result_smsg2);
					gtk_widget_show (t4_result_smsg6);
					gtk_widget_hide (t4_normal_smsg2);					
					gtk_widget_hide (t4_normal_smsg6);
				}
				if( strcmp(BP_test_msg, "Hypertension") == 0 ){
					gtk_widget_show (t4_result_smsg3);
					gtk_widget_show (t4_result_smsg7);
					gtk_widget_hide (t4_normal_smsg3);					
					gtk_widget_hide (t4_normal_smsg7);
				}
				if( strcmp(BP_test_msg, "Emergency Care required") == 0 ){
					gtk_widget_show (t4_result_smsg4);
					gtk_widget_show (t4_result_smsg8);
					gtk_widget_hide (t4_normal_smsg4);					
					gtk_widget_hide (t4_normal_smsg8);
				}
				g_print("msg has been read\n");
				//gtk_label_set_label (t5_label_sys_msg, BP_test_msg);
*/
				test5_button_set_state(TRUE);
				// bp_test_wait_start();
				feed_back = GTK_WIDGET (gtk_builder_get_object (Test5Builder, "label9"));
				gtk_label_set_label (feed_back, "Press OK to see ECG ");
				
				window = GTK_WIDGET (gtk_builder_get_object (Test5Builder, TEST5_WINDOW));
				gtk_widget_show_all(window);
				if(isQuickWellthCheck)
					test5_hide_next_button_n_image();
			}			
		}
	}
}

