#include <stdio.h>
#include <math.h>
#include <stdlib.h>
/*
#define N 26
#define M 26
#define T 10001


Each alphabet is a state, therefore accounting for 26 states.
M = 26 as there are 26 distinct observations in the ciphertext
*/

void readCipher(char * O, int T)
{
	int c,i;
	FILE *fp1;
	
	i=0;
	
	fp1 = fopen("Cipher.txt","r");
	if (fp1 == NULL)
		printf("\nInvalid Path provided for Cipher Text\n");

	while(i<T)
	{
		c = tolower(fgetc(fp1));
		if (c != EOF && c > 96 && c < 123  )
			O[i++] = c;
		else
			break;
	}
	fclose(fp1);

	
	 printf("\nThis is the observation matrix\n");
	
	// The part below can be used to verify that the input does not contain anything other than lower case letters
	
/*	printf("\nO[9999] : %c\tO[10000] : %c\n",O[9999],O[10000]);
	for(i=0;i<T;i++)
	{	
		if ( (int) O[i] < 96 || (int) O[i] > 123 )
			printf("%c\t%d\t%d",O[i],(int) O[i],i);
	}
*/	
}

void initialize_PI(double * PI, int N)
{
	int i,j;
	double randomNo = 0.0;
	double tempRandomNo = 0.0;
	double sum = 0.0;

	srand(time(NULL));

	for(i=0;i<N;i++)
	{

		tempRandomNo = (1.0/rand()) * 10000.0 ;
		randomNo = roundf(tempRandomNo * 1000000) / 1000000;

		if(randomNo <= 0.05 && (i % 2) == 0)	
		{	
			PI[i] = 1.0/N - (5*randomNo) ;
			PI[i] = roundf(PI[i] * 1000000)/1000000;
			sum += PI[i];
		}
		else if(randomNo <= 0.05 && (i % 2) != 0)	
		{
			PI[i] = 1.0/N + (5*randomNo);
			PI[i] = roundf(PI[i] * 1000000)/1000000;
			sum += PI[i];
		}		
		else if(randomNo > 0.05 && (i % 2) == 0)
		{		
			PI[i] = 1.0/N - (1.0/(100.0+randomNo));
			PI[i] = roundf(PI[i] * 1000000)/1000000;
			sum += PI[i];
		}		
		else if(randomNo > 0.05 && (i % 2) != 0)
		{		
			PI[i] = 1.0/N + (1.0/(100.0+randomNo));
			PI[i] = roundf(PI[i] * 1000000)/1000000;
			sum += PI[i];
		}
			
	}
	// The below part ensures that the sum of probabilities across the row in the PI matrix sums to 1.0	
	if (sum >= 1.0)
		PI[N-1] = PI[N-1] - (sum - 1.0);
	else
		PI[N-1] = PI[N-1] + (1.0 - sum);
}


void initialize_B(double ** B, int N, int M)
{
	int i,j;
	double hl,sum;
	
	// Generate Random values for B[N][M] where the values should be approximately near 0.037037 (1/27) and the sum of the row should be equal to 1.0
	for(i=0;i<N;i++)
	{
		sum = 0.0;
		for(j=0;j<M;j++)
		{ 
			if(j<=12)
			{
				hl = 60.0 * (j+1);
				B[i][j] = (1.0/M) - ( 1.0/hl ) ;
				sum += B[i][j];
				// printf("\nValue of B[%d][%d] is : %f.\tValue of sum is : %f. Value of hl is : %f.\n",i,j,B[i][j],sum,hl);
			}
			else if (j>=13 && j<=25)
			{
				hl = 60.0 * (j-12);
				B[i][j] = (1.0/M) + ( 1.0/hl ) ;
				sum += B[i][j];
				// printf("\nValue of B[%d][%d] is : %f.\tValue of sum is : %f. Value of hl is : %f.\n",i,j,B[i][j],sum,hl);
			}
		}
		
	}	
}


void print_A_B_PI(double A[26][26], double ** B, double * PI, int N, int M)
{
	int i,j;
	double *sumAcrossState = (double *)calloc(N, sizeof(double));
	double sum = 0.0;
	char alphabets[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};	

	// Print PI Matrix
	
	printf("\n\nPlease find below the PI matrix.\n\n");
	for(i=0;i<=N-1;i++)
	{
		printf("%f\t",PI[i]);
	}
	
	// Print A Matrix
	
	printf("\n\nPlease find below the A matrix.\n\n");
	for(i=0;i<=N-1;i++)
	{
		for(j=0;j<=N-1;j++)
		{
			printf("%f\t",A[i][j]);
		}
		printf("\n");
	}
	
	
	// Print B Matrix
	
	// Calculate the sum across row of B matrix and print it
	for(i=0;i<N;i++)
	{
		sum = 0.0;
		for(j=0;j<M;j++)
		{
				sum += B[i][j];
		}
		sumAcrossState[i] = sum;
	}
	
	// Printing the B matrix
	
	printf("\n\nPlease find below the B matrix");
	printf("\nLETTER\t");
	for(i=0;i<N;i++)
		printf("%c\t\t",alphabets[i]);
	
	printf("\n**************************************************************************************************************************************************************************\n");
	
	for(i=0;i<N;i++)
	{
		printf("\n\nSTATE[%c]",alphabets[i]);
		for(j=0;j<M;j++)
		{
			printf("\t%9f(%c)\t",B[i][j],alphabets[j]);
		}
	}

	printf("\n--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\nSUM");

	for(i=0;i<N;i++)
		printf("\t%9f\t",sumAcrossState[i]);

	printf("\n--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");

}


void computeAlphaPass(char * O, double * PI, double A[26][26], double ** B, double * c, double ** a, int N, int T )
{
	int i,j,t;
	double tempResult = 0.0;
	
	// Compute a(0)[i] (Alpha subscript 0)
	c[0] = 0 ;
	
	for (i=0;i<N;i++)
	{
		int asciiValue = (int) O[0];
		if( asciiValue > 96 &&  asciiValue < 123 )
			a[0][i] =  PI[i] * B[i][asciiValue - 97];
		
		c[0] = c[0] + a[0][i];
		// printf("\nValue of a[0][%d] : %f.\tValue of c[0] is :", i,a[0][i],c[0]);
		// printf("\nValue of O[0] : %c\t%d",O[0],O[0]-97);
		
	}
		
	//Scaling a[0][i]	
	c[0] = 1.0/c[0];
	
	for (i=0;i<N;i++)
	{
		a[0][i] =  c[0]*a[0][i];
		// printf("\nValue of a[0][%d] : %f", i,a[0][i]);
		
	}

	// Compute a(t)[i] .... a(T-1)[i]
	for(t=1;t<T;t++)
	{
		c[t] = 0;
		for(i=0; i <= N-1; i++)
		{
			a[t][i] = 0;
			for(j=0; j <= N-1; j++)
			{
				a[t][i] = a[t][i] + ( a[t-1][j] * A[j][i] );
			}
			
			int asciiValue = (int) O[t];
			if( asciiValue > 96 &&  asciiValue < 123 )
				a[t][i] = a[t][i] * B[i][asciiValue-97] ;
			
			c[t] = c[t] + a[t][i];
		//	printf("\nValue of a[%d][%d] : %f", t,i,a[t][i]);
		}
		
		// Scale a[t][i]
		c[t] = 1.0/c[t];
		// printf("\n\nValue of c[%d] is : %f",t,c[t]);
		for(i=0;i<N;i++)
		{
			a[t][i] = c[t]*a[t][i];
			// printf("\nFinal value of a[%d][%d] : %f.",t,i,a[t][i]);
		}
	}
	
	for(i=0; i <= N-1; i++)
	{
		tempResult += a[T-1][i];
	}

	// printf("\nFinal Result : Value of alpha pass for observation sequence O is : %f\n\n", tempResult);
	// printf("\nValue of the scaling factor is : %f %d\n\n",c[t-1],t-1);
	
}


void betaPass (double * c, double A[26][26],double ** B, char * O, double ** a, double ** b, int N, int T )
{
	int i,t,j;
	
	
	for(i=0;i<=N-1;i++)
	{
		b[T-1][i]=c[T-1];
		// printf("\nBeta Value : %f\n",b[T-1][i]);
	}

	for(t=T-2;t>=0;t--)
	{
		for(i=0;i<=N-1;i++)
		{
			b[t][i]=0;
			for(j=0;j<=N-1;j++)
			{
				int asciiValue = (int) O[t+1];

				if( asciiValue > 96 &&  asciiValue < 123 )
					b[t][i] = b[t][i] + (A[i][j])*(B[j][asciiValue - 97])*(b[t+1][j]);
				//else
					//printf("\nAfter loop.\t t : %d\ti : %d\tj : %d\n\n",t,i,j);
			}
			//Scaling BetaT[i] with the same scaling factor as alpha.
			//Scaling b[t][i] with the same factor as a[t][i];
			b[t][i] = c[t] * b[t][i];
		}
	}
// 	printf("\nBeta Value : %f %f\n",b[T-1][0],b[T-1][1]);
	
}

void computegammapass (double * c, double A[26][26],double ** B, char * O, double ** a, double ** b, double ** gamma, double *** gamma2, int N, int T )
{
	double denom;
	int i,j,t;
	
	for (t=0;t<=T-2;t++)
	{
		denom = 0.0;
		for (i=0;i<=N-1;i++)
		{
			for (j=0;j<=N-1;j++)
			{
				int asciiValue = (int) O[t+1];
				if( asciiValue > 96 &&  asciiValue < 123 )
					denom = denom + a[t][i]*A[i][j]*B[j][asciiValue - 97]*b[t+1][j];
			}
		}
		
		for(i=0;i<=N-1;i++)
		{
			gamma[t][i] = 0;
			for(j=0;j<=N-1;j++)
			{
				int asciiValue = (int) O[t+1];
				if( asciiValue > 96 &&  asciiValue < 123 )
				{	
					gamma2[t][i][j] = a[t][i] * A[i][j] * B[j][asciiValue - 97] * b[t+1][j]; 
				}
				gamma[t][i] = gamma[t][i] + gamma2[t][i][j];
				
				//if(t==0)
				//{
					//printf("\nValue of gamma2[%d][%d][%d] : %f.\tValue of gamma[%d][%d] : %f.\n",t,i,j,gamma2[t][i][j],t,i,gamma[t][i]);
					//printf("\nValue of a[%d][%d] : %f.\tValue of B[%d][%d] : %f.\tCharacter at O[%d] : %c. Ascii : %d\n",t,i,a[t][i],j,asciiValue-97,B[j][asciiValue - 97],t+1,O[t+1],asciiValue );
				//}
			}
		}
		
	}	

	// Special case for gamma[T-1][i]
	denom = 0.0;
	for(i=0;i<=N-1;i++)
	{
		denom = denom + a[T-1][i];
	}

	for(i=0;i<=N-1;i++)
	{
		gamma[T-1][i] = a[T-1][i]/denom;
	}

	//printf("\nValue of gamma[%d][%d] = %f.\tValue of gamma[%d][%d][%d] = %f.\n",t-1,i-1,gamma[t-1][i-1],t-1,i-1,j-1,gamma2[t-1][i-1][j-1]);
}


void reestimate_B_PI(double * PI, double ** gamma, double *** gamma2, double ** B, char * O, int N, int M, int T)
{
	
	int i,j,t;
	int maxSubscript = 0;
	double numer, denom, sum;
	double * sumAcrossStates = (double *)calloc(N, sizeof(double)) ;		
	double maxValue = 0.000000;

	// Re-estimate PI matrix

	sum = 0.0;

	for(i=0;i<N;i++)	
	{	
		PI[i] = ( ( roundf( gamma[0][i] * 1000000 ) / 1000000 ) >= 0.0 ? ( roundf( gamma[0][i] * 1000000 ) / 1000000 ) : 0.0  );
		PI[i] = ( (PI[i] > 1.000000) ? 1.000000 : PI[i] ) ;
		if (PI[i] < 0.0)
			printf("\nPI[%d] : %f",i,PI[i]);
		sum += PI[i];
	}
	// printf("\n\nPI[3] = %f\tSum : %f",PI[2],sum);
	// Bookkeeping to maintain the sum of all probabilities across the row in PI matrix to 1.0		

	if(sum >= 1.000000)
	{
		for(i=0;i<N;i++)
		{
			if (PI[i] > maxValue)
			{
				maxSubscript = i;
				maxValue = PI[i];
			}
		}
		PI[maxSubscript] = PI[maxSubscript] - (sum-1.000000) ;
			
	}	
	else
	{
		PI[0] = PI[0] + (1.0-sum);
	}
	

	// Re-estimate B matrix

	for(i=0;i<N;i++)
	{
		sum = 0.0;
		sumAcrossStates[i] = 0.0;
		for(j=0;j<M;j++)
		{
			numer = 0.0;
			denom = 0.0;
			for(t=0;t<=T-1;t++)
			{
				int asciiValue = (int) O[t];
				if( asciiValue > 96 &&  asciiValue < 123 )
				{
					if ( (asciiValue-97) == j )
						numer = numer + gamma[t][i];
				}
			
				denom = denom + gamma[t][i];
			}

			// Bookkeeping to maintain the sum of all probabilities across the row in B matrix to 1.0		
			B[i][j] = ( ( roundf( (numer/denom) * 1000000 ) / 1000000 ) >= 0.0 ? ( roundf( (numer/denom) * 1000000 ) / 1000000 ) : 0.0  );

			sum += B[i][j];
		}

		// Bookkeeping to maintain the sum of all probabilities across the row in B matrix to 1.0		
		sumAcrossStates[i] = sum;
		if (sumAcrossStates[i] > 1.000000)
		{
			for(j=0;j<M;j++)
			{
				if ( B[i][j] > 2*(sumAcrossStates[i]-1.0) )  
				{
					B[i][j] -= (sumAcrossStates[i]-1.0);
					break;
				}
				//if (B[i][j] < 0.0)
				//	printf("\nB : %f\tSum : %f", B[i][j],(sumAcrossStates[i]-1.0)/( (double) M));

			}
		}		
		else if (sumAcrossStates[i] < 1.000000)
		{
			B[i][j-1] = B[i][j-1] + (1.0 - sumAcrossStates[i]);
		}
	}
	
}

double computeLogP(double * c, int T)
{
	
	double logProb = 0.0;
	int i;
	
	for(i=0;i<=T-1;i++)
	{
			logProb = logProb + log(c[i]);
	}
	logProb = -logProb;
	
	return logProb;
}

void printKey(double ** B, int N, int M)
{

	int i,j,maxValueSubscript;
	double maxValue;
	char alphabets[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};	

	j=0;
	while(j<26)
	{
		maxValue = 0.0;
		maxValueSubscript = 0;
		
		for(i=0;i<N;i++) // These are the states
		{
			if( B[i][j] > maxValue )
			{
				maxValue = B[i][j];
				maxValueSubscript = i;

			}
			if (i == 25)
				printf("\nSTATE : %c\tValue : %f\tCipher text Letter : %c ",alphabets[maxValueSubscript],maxValue,alphabets[j]);
		}
		j++;
	}

}

int main()
{

	int i,j,T,N,M;
	int maxIters = 800;
	int iters = 0;
	double oldLogProb = -(1.0/0.0);

	printf("\nPlease enter a value for N : ");
	scanf("%d", &N);

	printf("\nPlease enter a value for M : ");
	scanf("%d", &M);

	printf("\nPlease enter a value for T : ");
	scanf("%d", &T);


	char *O = (char *)calloc(T, sizeof(char));
	double *PI = (double *)calloc(N, sizeof(double));

	double A[26][26] = {
		{0.00320,0.02153,0.04721,0.04476,0.00113,0.01417,0.02455,0.00459,0.04017,0.00195,0.01100,0.09790,0.03810,0.18396,0.00281,0.02016,0.00058,0.11674,0.10182,0.14237,0.01213,0.01929,0.01127,0.00346,0.03671,0.00096},
		{0.11677,0.00882,0.00294,0.00257,0.28906,0.00196,0.00135,0.00257,0.06274,0.00539,0.00086,0.11089,0.00368,0.00110,0.11898,0.00196,0.00061,0.06163,0.01507,0.00821,0.10758,0.00270,0.00306,0.00061,0.08087,0.00074},
		{0.12775,0.00182,0.01820,0.00276,0.14564,0.00195,0.00151,0.15442,0.06808,0.00050,0.04700,0.03633,0.00144,0.00113,0.21447,0.00295,0.00125,0.03915,0.00734,0.09192,0.02893,0.00088,0.00169,0.00031,0.00866,0.00044},
		{0.11143,0.03926,0.02247,0.02257,0.17153,0.02531,0.01887,0.02800,0.11168,0.00538,0.00203,0.02105,0.03089,0.01643,0.07080,0.01856,0.00218,0.03256,0.06167,0.10326,0.03479,0.00771,0.02906,0.00025,0.01709,0.00046},
		{0.07743,0.01878,0.05059,0.08977,0.03883,0.02537,0.01513,0.01586,0.02962,0.00308,0.00602,0.04128,0.03728,0.10133,0.02457,0.02857,0.00321,0.14522,0.10970,0.06244,0.00743,0.01720,0.02802,0.01121,0.01318,0.00055},
		{0.09529,0.01090,0.02072,0.01045,0.08011,0.06725,0.00831,0.01768,0.11789,0.00366,0.00223,0.02635,0.01527,0.00911,0.19711,0.01393,0.00116,0.08109,0.02206,0.15442,0.03403,0.00259,0.01206,0.00045,0.00447,0.00071},
		{0.11690,0.01263,0.01426,0.00916,0.17240,0.01477,0.01527,0.11487,0.08513,0.00305,0.00204,0.02363,0.01466,0.03248,0.09888,0.01171,0.00112,0.09430,0.03371,0.08004,0.03574,0.00234,0.01609,0.00051,0.00438,0.00051},
		{0.15953,0.00460,0.00702,0.00310,0.47986,0.00337,0.00246,0.00667,0.11739,0.00095,0.00067,0.00417,0.00564,0.00722,0.09826,0.00460,0.00040,0.01921,0.01163,0.04139,0.01171,0.00127,0.00833,0.00020,0.00425,0.00024},
		{0.03055,0.00961,0.07411,0.04589,0.04204,0.01470,0.02892,0.00143,0.00087,0.00034,0.00511,0.06298,0.02881,0.25476,0.07959,0.01029,0.00082,0.03654,0.11632,0.11750,0.00126,0.02976,0.00138,0.00242,0.00020,0.00672},
		{0.15358,0.00524,0.00785,0.00611,0.13962,0.00436,0.00524,0.00960,0.04538,0.00698,0.00436,0.00611,0.00785,0.00524,0.30716,0.00611,0.00436,0.04538,0.00873,0.00611,0.28010,0.00436,0.00785,0.00436,0.00436,0.00436},
		{0.07177,0.01196,0.01892,0.00918,0.33324,0.01530,0.00640,0.03310,0.14604,0.00668,0.00417,0.02865,0.01363,0.04896,0.05285,0.01113,0.00195,0.01363,0.09513,0.05202,0.00807,0.00306,0.02587,0.00139,0.01446,0.00139},
		{0.12834,0.01892,0.01501,0.06400,0.16603,0.01644,0.00701,0.00801,0.12104,0.00133,0.00581,0.14211,0.01601,0.00486,0.07449,0.01549,0.00076,0.01020,0.04380,0.03479,0.02540,0.00705,0.01034,0.00024,0.06710,0.00038},
		{0.18651,0.03753,0.00859,0.00347,0.25011,0.00565,0.00188,0.00678,0.11718,0.00143,0.00121,0.00445,0.04491,0.00317,0.11831,0.06232,0.00045,0.04039,0.02999,0.02720,0.03617,0.00083,0.00784,0.00038,0.01063,0.00045},
		{0.07549,0.01200,0.05159,0.14048,0.08897,0.01677,0.10857,0.01370,0.06055,0.00385,0.00907,0.01148,0.01511,0.02065,0.06210,0.01120,0.00078,0.00757,0.07067,0.17194,0.01225,0.00732,0.01633,0.00036,0.01350,0.00058},
		{0.02177,0.01789,0.02276,0.02172,0.00739,0.10623,0.01114,0.00997,0.01218,0.00167,0.00917,0.04448,0.06516,0.18545,0.03081,0.03009,0.00048,0.14231,0.04094,0.05886,0.09193,0.02281,0.03972,0.00133,0.00603,0.00048},
		{0.13793,0.00381,0.00273,0.00254,0.16429,0.00449,0.00195,0.02987,0.06121,0.00146,0.00156,0.10045,0.01415,0.00098,0.13120,0.05476,0.00059,0.18167,0.02323,0.03954,0.04110,0.00059,0.00547,0.00049,0.00361,0.00049},
		{0.01071,0.01071,0.01071,0.01071,0.01285,0.01071,0.01071,0.01285,0.01071,0.01071,0.01071,0.01071,0.01071,0.01071,0.01071,0.01285,0.01071,0.01071,0.01071,0.01071,0.94861,0.01071,0.01071,0.01071,0.01071,0.01071},
		{0.10267,0.01015,0.02458,0.03757,0.21735,0.01142,0.01809,0.01295,0.09406,0.00268,0.01517,0.01803,0.03055,0.02846,0.10203,0.01446,0.00034,0.02009,0.08455,0.08012,0.02074,0.01086,0.01378,0.00015,0.03185,0.00049},
		{0.10195,0.02292,0.03705,0.01425,0.10867,0.02126,0.00828,0.05316,0.09497,0.00358,0.00864,0.01735,0.02410,0.01292,0.07702,0.03774,0.00160,0.01126,0.07181,0.19948,0.03470,0.00265,0.03048,0.00015,0.00693,0.00021},
		{0.07104,0.01045,0.01241,0.00547,0.11119,0.00964,0.00362,0.30486,0.11296,0.00157,0.00192,0.01560,0.01139,0.00554,0.11451,0.00848,0.00041,0.04002,0.04227,0.05523,0.01959,0.00135,0.02155,0.00011,0.02024,0.00085},
		{0.03310,0.03913,0.04880,0.02923,0.04857,0.00750,0.03642,0.00147,0.02753,0.00186,0.00247,0.09365,0.03047,0.15614,0.00340,0.04176,0.00046,0.13959,0.12845,0.12977,0.00046,0.00240,0.00124,0.00093,0.00263,0.00062},
		{0.08327,0.00180,0.00120,0.00260,0.61242,0.00160,0.00120,0.00180,0.21845,0.00180,0.00120,0.00160,0.00399,0.00120,0.05531,0.00240,0.00100,0.00240,0.00439,0.00339,0.00339,0.00180,0.00359,0.00100,0.00699,0.00100},
		{0.20303,0.00723,0.00587,0.00644,0.15741,0.00565,0.00282,0.15842,0.20246,0.00282,0.00226,0.00734,0.00949,0.03771,0.12048,0.00621,0.00079,0.01400,0.02179,0.01705,0.00215,0.00113,0.00689,0.00056,0.01107,0.00068},
		{0.14056,0.02711,0.09036,0.01004,0.09839,0.01406,0.00703,0.02510,0.08735,0.00502,0.00904,0.01707,0.01606,0.00703,0.03414,0.26807,0.00502,0.01205,0.01506,0.16064,0.00803,0.00602,0.02008,0.00602,0.01004,0.00502},
		{0.10465,0.04215,0.04298,0.02598,0.10141,0.03149,0.01425,0.04227,0.06334,0.00778,0.00431,0.02634,0.04346,0.02191,0.09794,0.03161,0.00180,0.02419,0.10022,0.11566,0.00682,0.00467,0.05280,0.00060,0.00311,0.00072},
		{0.21689,0.01142,0.02055,0.01826,0.42694,0.01370,0.01370,0.02283,0.09361,0.01370,0.01370,0.03425,0.01826,0.01142,0.05708,0.01370,0.01142,0.01826,0.02283,0.02511,0.03425,0.01598,0.01826,0.01142,0.02740,0.05251}};
	
	double **B = (double **)calloc(N, sizeof(double *));
	for(i=0;i<N;i++)
		B[i] = (double *)calloc(M, sizeof(double));
	
	/* These are the scaling factor, alpha and beta pass matrices*/
	double *c = (double *)calloc(T, sizeof(double));

	double **a = (double **)calloc(T, sizeof(double *));
	for(i=0;i<T;i++)
		a[i] = (double *)calloc(N, sizeof(double));

	double **b = (double **)calloc(T, sizeof(double *));
	for(i=0;i<T;i++)
		b[i] = (double *)calloc(N, sizeof(double));

	/* These are the gamma and di-gamma matrices*/

	double **gamma = (double **)calloc(T, sizeof(double *));
	for(i=0;i<T;i++)
		gamma[i] = (double *)calloc(N, sizeof(double));

	double ***gamma2  = (double ***)calloc(T, sizeof(double **));
	for(i=0;i<T;i++)
		gamma2[i] = (double **)calloc(N, sizeof(double *));
	for(i=0;i<T;i++)
	{
		for(j=0;j<N;j++)
		{
			gamma2[i][j] = (double *)calloc(M, sizeof(double));
		}
	}
	
	printf("\nValue of LogProb : %f", oldLogProb);

	readCipher(O, T);
	initialize_PI(PI, N);	
	initialize_B(B, N, M);	
	print_A_B_PI(A, B, PI, N, M);	

	computeAlphaPass(O, PI, A, B, c, a, N, T );
	
	betaPass(c, A, B, O, a, b, N, T );
	
	computegammapass(c, A, B, O, a, b, gamma, gamma2, N, T );

	reestimate_B_PI(PI, gamma, gamma2, B, O, N, M, T);

	printf("\n\nPlease find below the values of PI, A and B matrices after the initial pass.\n---------------------------------------------------------------------------------\n");
	print_A_B_PI(A, B, PI, N, M);	

	double newLogProb = 0.0;	
	newLogProb = computeLogP(c, T);
	
	printf("\nValue of Log Prob after initial pass is : %f\n",newLogProb);

	iters += 1;

//	while (iters < maxIters && newLogProb > oldLogProb) //This statement is not used as we reach a local maxima after the 3rd iteration
	while (iters < maxIters)
	{
		oldLogProb = newLogProb;

		computeAlphaPass(O, PI, A, B, c, a, N, T );
	
		betaPass(c, A, B, O, a, b, N, T );
	
		computegammapass(c, A, B, O, a, b, gamma, gamma2, N, T );

		reestimate_B_PI(PI, gamma, gamma2, B, O, N, M, T);

		newLogProb = computeLogP(c, T);

		iters++;

//		printf("\nNo of iterations elapsed : %d", iters);
	}
	
	printf("\nNo of iterations elapsed : %d.\nCurrent LogProb : %f\t Previous LogProb : %f\n",iters-1,newLogProb,oldLogProb);

	printf("\n\nPlease find below the values of PI, A and B matrices after the final iteration.\n---------------------------------------------------------------------------------\n");
	print_A_B_PI(A, B, PI, N, M);	

	printKey(B, N, M);

	printf("\n\nThe program has run to successful completion.\n\n");

	return 0;
}