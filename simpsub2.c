#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <math.h>
#include "Hashtbl.h"

#define MAXITER 10000

char abc[] = "abcdefghijklmnopqrstuvwxyz ";
double** mCipher;
double** mSample;
HashTable hSample, hCipher;
char* bufSample;
char* bufCipher;
int numsymbols;
char spaces;

void die (char s[])
{
	printf ("%s", s);
	exit (1);
}

void deleteblanks (int filesize)
{
	int i = 0, j = 0;
	char* tempbuf;

	tempbuf = (char*) malloc (filesize * sizeof(char));

	while (bufSample[i] != '\0')
	{
		if (bufSample[i] != ' ')
		{
			tempbuf[j] = bufSample[i];
			j++;
		}
		i++;
	}
	tempbuf[j] = '\0';

	strcpy (bufSample, tempbuf);
	free (tempbuf);
}

void deleteblanks2 (int filesize)
{
	int i = 0, j = 0;
	char* tempbuf;

	tempbuf = (char*) malloc (filesize * sizeof(char));

	while (bufCipher[i] != '\0')
	{
		if (bufCipher[i] != ' ')
		{
			tempbuf[j] = bufCipher[i];
			j++;
		}
		i++;
	}
	tempbuf[j] = '\0';

	strcpy (bufCipher, tempbuf);
	free (tempbuf);
}

void initmatrices ()
{
	int i, j;
	/* allocate memory for the matrices */

	mSample = (double**) malloc (numsymbols * sizeof(double*));
	mCipher = (double**) malloc (numsymbols * sizeof(double*));

	if (mSample == NULL || mCipher == NULL)
		die ("Could not allocate matrices\n");

	for (i = 0; i < numsymbols; i++)
	{
		mSample[i] = (double*) malloc (numsymbols * sizeof(double));
		mCipher[i] = (double*) malloc (numsymbols * sizeof(double));
	}

	for (i = 0; i < numsymbols; i++)
	{
		for (j = 0; j < numsymbols; j++)
		{
			mSample[i][j] = 0.;
			mCipher[i][j] = 0.;
		}
	}
}

int fsize (char name[])
{
	struct stat stbuf;
	if (stat (name, &stbuf) == -1)
		return -1;
	return stbuf.st_size;
}

int readsample (FILE* fp, int filesize)
{
	int numread, hashindex, i = 0;
	char* p1;
	char* p2;
	char tempstr[2];

	/* first, read in the whole file, without parsing */
	numread = fread (bufSample, sizeof(char), filesize, fp);
	/* append null terminator to end -- fread doesn't do it! */
	bufSample[numread] = '\0';

	/* if necessary delete blanks */
	if (spaces == 'n')
		deleteblanks (filesize);

	/* now, go through the file and encode valid digrams */
	while (bufSample[i] != '\0')
	{
		bufSample[i] = tolower (bufSample[i]);
		if (bufSample[i+1] != '\0')
			bufSample[i+1] = tolower (bufSample[i+1]);
		p1 = strchr (abc, bufSample[i]);
		p2 = strchr (abc, bufSample[i+1]);
		if (i < filesize - 1 && p1 != NULL && p2 != NULL)
		{
			/* store this block */
			tempstr[0] = bufSample[i];
			tempstr[1] = bufSample[i+1];

			hashindex = FindIndex (&hSample, tempstr);

			if (hashindex != -1)
				IncrFreq (&hSample, hashindex);						
			else
				AddPtrEntry (&hSample, bufSample+i);
		}
		i++;
	}
	return i-1;
}

void buildsamplematrix (int pairnum)
{
	int i, j, hashindex;
	char tempstr[2];

	for (i = 0; i < numsymbols; i++)
	{
		tempstr[0] = abc[i];
		for (j = 0; j < numsymbols; j++)
		{
			tempstr[1] = abc[j];

			hashindex = FindIndex (&hSample, tempstr);
			if (hashindex != -1)
				mSample[i][j] = (double)(hSample.freq[hashindex]) / (double)pairnum;
			else
				mSample[i][j] = 0;
		}
	}
}

int readcipher (FILE* fp, int filesize)
{
	int numread, hashindex, i = 0;
	char* p1;
	char* p2;
	char tempstr[2];

	/* first, read in the whole file, without parsing */
	numread = fread (bufCipher, sizeof(char), filesize, fp);
	/* append null terminator to end -- fread doesn't do it! */
	bufCipher[numread] = '\0';

	if (spaces == 'n')
	  deleteblanks2 (filesize);

	/* now, go through the file and encode valid digrams */
	while (bufCipher[i] != '\0')
	{
		bufCipher[i] = tolower(bufCipher[i]);
		if (bufCipher[i+1] != '\0')
			bufCipher[i+1] = tolower(bufCipher[i+1]);
		p1 = strchr (abc, bufCipher[i]);
		p2 = strchr (abc, bufCipher[i+1]);
		if (i < filesize - 1 && p1 != NULL && p2 != NULL)
		{
			/* store this block */
			tempstr[0] = bufCipher[i];
			tempstr[1] = bufCipher[i+1];

			hashindex = FindIndex (&hCipher, tempstr);

			if (hashindex != -1)
				IncrFreq (&hCipher, hashindex);						
			else
				AddPtrEntry (&hCipher, bufCipher+i);
		}
		i++;
	}
	return i-1;
}

void buildciphermatrix (int pairnum)
{
	int i, j, hashindex;
	char tempstr[2];

	for (i = 0; i < numsymbols; i++)
	{
		for (j = 0; j < numsymbols; j++)
		{
			tempstr[0] = abc[i];
			tempstr[1] = abc[j];

			hashindex = FindIndex (&hCipher, tempstr);
			if (hashindex != -1)
				mCipher[i][j] = (double)(hCipher.freq[hashindex]) / (double)pairnum;
			else
				mCipher[i][j] = 0;
		}
	}
}

void exch (int n1, int n2, int colflag)
{
	/* if colflag = 0, exch rows; otherwise, columns */
	int i;
	double temp;

	if (colflag == 0)
	{
		for (i = 0; i < numsymbols; i++)
		{
			temp = mCipher[n1][i];
			mCipher[n1][i] = mCipher[n2][i];
			mCipher[n2][i] = temp;
		}
	}
	else
	{
		for (i = 0; i < numsymbols; i++)
		{
			temp = mCipher[i][n1];
			mCipher[i][n1] = mCipher[i][n2];
			mCipher[i][n2] = temp;
		}
	}
}

double recalcfunc ()
{
	double sum = 0;
	int i, j;

	for (i = 0; i < numsymbols; i++)
		for (j = 0; j < numsymbols; j++)
			sum += fabs (mSample[i][j] - mCipher[i][j]);
	
	return sum;
}


void play (double initfunc)
{
	/* this is the main algorithm */
	char key[] = "abcdefghijklmnopqrstuvwxyz ";
	char keynormal[] = "abcdefghijklmnopqrstuvwxyz ";
	char temp;
	char* p;
	double func;
	int n1, n2, i = 0;
	int nochange = 0;

	if (spaces == 'n')
	{
		key[26] = '\0';
		keynormal[26] = '\0';
	}

	srand ((unsigned)time (NULL));

	while (nochange < MAXITER)
	{
		n1 = rand () % numsymbols;
		n2 = n1 + (rand () % (numsymbols - n1));

		exch (n1, n2, 0);
		exch (n1, n2, 1);

		func = recalcfunc ();
		if (func >= initfunc)		/* worse, go to prior settings! */
		{
			exch (n2, n1, 0);
			exch (n2, n1, 1);
			nochange++;
		}
		else							/* better, save changes! */
		{
			nochange = 0;
			initfunc = func;
			/* swap letters in the key string */
			temp = key[n1];
			key[n1] = key[n2];
			key[n2] = temp;
		}
	}

	printf ("DONE! Func value=%f\n", func);
	printf ("Key is: %s\n", abc);
	printf ("        %s\n", key);

	/* change the buffer */
	while (bufCipher[i] != '\0')
	{
		p = strchr (key, bufCipher[i]);
		if (p != NULL)
			bufCipher[i] = keynormal[p-key];
		i++;
	}

	printf ("%s\n", bufCipher);
}

void main ()
{
	char samplename[256];
	char ciphername[256];
	FILE* fpCipher;
	FILE* fpSample;
	int samplefilesize, cipherfilesize, samplepairnum, cipherpairnum, i;

	bufSample = NULL; bufCipher = NULL;
	printf ("Name of sample (\"learning\") file: ");
	scanf ("%s", samplename);
	fflush (stdin);

	fpSample = fopen (samplename, "r");
	if (fpSample == NULL)
		die ("Could not open sample file\n");

	printf ("Name of cipher file: ");
	scanf ("%s", ciphername);
	fflush (stdin);

	fpCipher = fopen (ciphername, "r");
	if (fpCipher == NULL)
		die ("Could not open cipher file\n");

	printf ("Is the cipher formatted with spaces? (y/n): ");
	scanf ("%c", &spaces);
	fflush (stdin);
	spaces = tolower (spaces);

	if (spaces == 'y')
		numsymbols = 27;
	else
	{
		numsymbols = 26;
		abc[26] = '\0';
	}

	samplefilesize = fsize (samplename);
	cipherfilesize = fsize (ciphername);
	bufSample = (char*) malloc (samplefilesize * sizeof(char));
	bufCipher = (char*) malloc (cipherfilesize * sizeof(char));
	if (bufSample == NULL || bufCipher == NULL)
		die ("Could not allocate buffers for files\n");

	initmatrices ();
	InitHashTable (&hSample, samplefilesize * 3);
	InitHashTable (&hCipher, cipherfilesize * 3);

	/* analyze the sample file: hash digrams, etc. */
	printf ("Reading sample file...\n");
	samplepairnum = readsample (fpSample, samplefilesize);

	/* build the sample matrix */
	printf ("Analyzing sample file...\n");
	buildsamplematrix (samplepairnum);

	/* analyze the cipher file: hash digrams, etc. */
	printf ("Reading cipher file...\n");
	cipherpairnum = readcipher (fpCipher, cipherfilesize);

	/* build the cipher matrix */
	printf ("Analyzing cipher file...\n");
	buildciphermatrix (cipherpairnum);

	/* at this point, all the arrays and hashes are filled and computed
		and ready to be used */


	printf ("Initial closeness is %f, PLEASE WAIT...\n", recalcfunc ());
	play (recalcfunc ());

	fclose (fpSample);
	fclose (fpCipher);

	free (bufSample);
	FreeHashTable (&hSample);
	FreeHashTable (&hCipher);

	for (i = 0; i < numsymbols; i++)
	{
		free (mSample[i]);
		free (mCipher[i]);
	}
	free (mSample);
	free (mCipher);
}

