#include <stdio.h>


int readdump()
{
FILE *fp,*ffp,*sfp;
char ReadBuf[256],FirstBuf[32],SecBuf[32],DumpBuf[256];
int BreakFlag,FirstVal,SecVal,Temp,LineCount,NumRead,MaskVal,TimeVal;
int FirstVal1,FirstVal2,SecVal1,SecVal2,FirstAve,SecAve;

	fp = fopen("../data/EcgDump_2", "r");
	ffp = fopen("../data/FirstDump_2", "w+");
	sfp = fopen("../data/SecDump_2", "w+");
			
	BreakFlag = 1;
	LineCount = 0;
	FirstVal1 = FirstVal2 = SecVal1 = SecVal2 = 0;

	while (BreakFlag)
	{
/***
//        	NumRead = fread(ReadBuf,11,1,fp);
		fgets(DumpBuf,15,fp);
		sscanf(DumpBuf,"%d %s\n",&TimeVal,ReadBuf);
***/
		fgets(ReadBuf,15,fp);
		
		printf(" %s \n",ReadBuf);
		if (feof(fp))
			break;
		//if (DumpBuf == NULL)
		if (ReadBuf == NULL)
		{
			if (feof(fp))
				break;
			else
				continue;
		}
		else
		{
			if (!((ReadBuf[0] == 'S') && (ReadBuf[9] == 'T')))
				continue;
			
			strncpy(FirstBuf,&ReadBuf[1],4);
			FirstBuf[4] = '\0';
			strncpy(SecBuf,&ReadBuf[5],4);
			SecBuf[4] = '\0';

			sscanf(FirstBuf,"%X",&FirstVal);
			sscanf(SecBuf,"%X",&SecVal);
			sscanf("03FF","%X",&MaskVal);

			Temp = (FirstVal & MaskVal) ;
			FirstVal = Temp;
			Temp = (SecVal & MaskVal) ;
			SecVal = Temp;

	
			FirstVal -= 512;
			SecVal -= 512;

 			FirstVal = FirstVal * -1;
			SecVal = SecVal * -1;


			FirstAve = (FirstVal1 + FirstVal2 + FirstVal) / 3;
			SecAve = (SecVal1 + SecVal2 + SecVal ) / 3;
			SecVal2 = SecVal1;
			SecVal1 = SecVal;
			FirstVal2 = FirstVal1;
			FirstVal1 = FirstVal;

/***
//			fprintf(ffp,"%d	%d \n",LineCount,FirstVal);
//			fprintf(sfp,"%d	%d \n",LineCount,SecVal);
//			Discard first few data points
			if (LineCount > 7)
			{
			fprintf(ffp,"%d	%d \n",TimeVal,FirstAve);
			fprintf(sfp,"%d	%d \n",TimeVal,SecAve);
			}
***/
			fprintf(ffp,"%d \n",FirstAve);
			fprintf(sfp,"%d \n",SecAve);
			LineCount++;


		}

	}
	
	fclose(fp);
	fclose(ffp);
	fclose(sfp);
	return(1);


}
