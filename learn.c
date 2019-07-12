
#include<stdio.h> 
#include<stdlib.h>

double** matrixT; 
double** mult;
double** MatrixI;
double ** identity;
double** inverse1;

int row1; 
int row2; 
int col1;
int col2;

void multiply(double** Matrix1,int row1,int col1,double** Matrix2,int row2, int col2){
int i,j,k;
double sum;
	sum =0.0;
	// memory allocation 
	mult = malloc(row1 * sizeof(double*));
	for(i=0;i<row1;i++){
		mult[i]=malloc(col2 * sizeof(double*));
	}
// case in which matrix cant be multipled.
//if(col1!=row2){
//printf("matrix can't be multiplied\n");
//	exit(0);
//}
// multiplication loop
	for(i=0;i<row1;i++){
		for(j=0;j<col2;j++){
			for(k=0;k<row2;k++){
			sum = sum + Matrix1[i][k] * Matrix2[k][j]; 
			}
			mult[i][j] = sum;
			sum= 0.0000000;
		}
	}	

} 
void print(double** y,int rows,int col){
int i,j;
for (i=0;i<rows;i++){
	for(j=0;j<col;j++){
	printf("%lf ",y[i][j]);	
	}
	printf("\n");
}

}

void inverse(double** matrix, int rows){
int i;
int j; 
int k; 
	//memory allocation
	int size = 2*rows; 
	 MatrixI=malloc(rows*(sizeof(double*)));
	 for(i=0;i<rows;i++){
		MatrixI[i] = malloc(size*(sizeof(double)));
	}
	//filling the matrix; 
	for(i=0;i<rows;i++){
		for(j=0;j<rows;j++){
		MatrixI[i][j] = matrix[i][j];
		}
	}
	//2nd half
	for(i=0;i<rows;i++){
             for(j=0;j<rows;j++){
                MatrixI[i][j+rows]=identity[i][j];
            }
     }
		//prints augmented 
//	print(MatrixI,rows,size);
		
	//	printf("\n");
		
		
		//gauss
//		printf("rows:%d\n",rows);
		
	for(i=0;i<rows;i++){
		if(MatrixI[i][i]!=1)
		{
			double number = MatrixI[i][i];
			
				for(j=0;j<size;j++)
				{
			MatrixI[i][j] = MatrixI[i][j]/number;				}
		}
			for(k=0;k<rows;k++){
			if(k==i){
			continue;
			}
			else if(MatrixI[k][i]!=0){
		double number= MatrixI[k][i];
			for(j=0;j<size;j++){
			MatrixI[k][j]=MatrixI[k][j]-(number * MatrixI[i][j]);
	}
			}	
		}
	}
	
	//print(MatrixI,rows,size);
	//printf("\n");
	//fill
	inverse1 = malloc(rows*sizeof(double*));
	for(i=0;i<rows;i++){
		inverse1[i]=malloc(rows*sizeof(double));
	}
	
	for(i=0;i<rows;i++){	
		for(j=rows;j<size;j++){
			inverse1[i][j-rows] = MatrixI[i][j];		
		}
	}
	//printf("inverse1:\n");
	//print(inverse1,rows,rows);
}
//-----------------------------------------------------------

	
	
int main( int argc, char ** argv){
int i;//for for loop x  
int j;// for for loop y
int rows;// number of training data 
int columns; // number of attributes
	FILE *file; 
	file = fopen(argv[1],"r");
	fscanf(file,"%d \n",&columns);
	fscanf(file,"%d \n",&rows);
	//memory allocation of the 2D array 	
	int includeYcolumn = columns+1;
	double ** matrixY; 
	matrixY = malloc(rows*(sizeof(double*)));
	for(i=0;i<rows;i++){
		matrixY[i] = malloc(includeYcolumn*sizeof(double*));
	}
	//filing the 2D array
	for(i=0;i<rows;i++){
		for(j=0;j<includeYcolumn;j++){
		fscanf(file,"%lf,",&matrixY[i][j]);
		}
	}
	fclose(file);
	//printing the array 
//	printf("matrix with y\n");	
//	print(matrixY,rows,columns+1);
//-----------------------------------------------------------------------
	// matrix withoutY; 
//	printf("Matrix without Y\n");
	double** matrix; 
	matrix = malloc(rows*(sizeof(double*)));
	for(i=0;i<rows;i++){
		matrix[i] = malloc(columns*sizeof(double*));
	}

	//filing the 2D array
	for(i=0;i<1;i++){
		for(j=0;j<1;j++){
		matrix[i][j]= 1;
		}
	}

	for(i=0;i<rows;i++){
		for(j=0;j<columns;j++){
		matrix[i][j]= matrixY[i][j];
		}
	}
	// printing matric without Y 
//	print(matrix,rows,columns);
//	printf("\n");
//--------------------------------------------------------------------------
	// identity matrix 
//	printf("identity matrix\n");
	// allocation
	identity = malloc(rows * sizeof(double*));
	for(i=0;i<rows;i++){
		identity[i]=malloc(rows * sizeof(double*));
	}
	//fill
	for(i=0;i<rows;i++){
		for(j=0;j<rows;j++){
		if(i==j){
		identity[i][j] = 1.0; 
		}
		else{
		}
		}
	}
	//print
//	print(identity,rows,rows);
//---------------------------------------------------------------------
 // augmented matrix 
 //	printf("\n");
//	printf("augmented matrix\n");

	double** aug; 
	int include1s = columns + 1; 
	aug = malloc(rows * sizeof(double *));
	// memory allocation 
	for(i=0;i<rows;i++){
		aug[i]=malloc((include1s) * sizeof(double*));
	}
//	print(aug,rows,include1s);
	// gets column of 1s 
	for(i=0;i<rows;i++){
		for(j=0;j<1;j++){
		aug[i][0] = 1; 
		}
	}
	// fill the rest
	for(i=0;i<rows;i++){
		for(j=1;j<columns+1;j++){
		aug[i][j]= matrix[i][j-1];
		}
	}
//	print(aug,rows,include1s);

//---------------------------------------------------------------------
	// transpose of augmented matrix
//	printf("\n");
//	printf("transpose of augmented matrix\n");

 double** matrixTA;
	// malloc
	matrixTA = malloc(include1s *(sizeof(double*)));
	for(i=0;i<include1s;i++){
		matrixTA[i]=malloc(rows*sizeof(double*));
	}
	//fill 
	for(i=0;i<rows;i++){
		for(j=0;j<include1s;j++){
		matrixTA[j][i]=aug[i][j];
		}
	}
//	print(matrixTA,include1s,rows);
//--------------------------------------------------------------------
	//matrix with 1s 
//	printf("rows:%d\n",rows);
//	printf("columns:%d\n",columns);
//	printf("columns+1:%d\n",include1s);
	
	double ** matrix1; 
	matrix1 = malloc(rows*(sizeof(double*)));
	for(i=0;i<rows;i++){
		matrix1[i] = malloc(include1s*sizeof(double*));
	}
	//gets ones columns
	for(i=0;i<rows;i++){
		for(j=0;j<1;j++){
		matrix1[i][0] = 1; 
		}
	}
	//gets rest
	for(i=0;i<rows;i++){
		for(j=1;j<columns+1;j++){
		matrix1[i][j]= matrix[i][j-1];
		}
	} 
	
	double** matrix1T;
	// malloc
	
	matrix1T=malloc(include1s*sizeof(double*));
	for(i=0;i<include1s;i++){
			matrix1T[i]=malloc(rows*sizeof(double*));
	}
	//fill 
	for(i=0;i<rows;i++){
		for(j=0;j<include1s;j++){
		matrix1T[j][i] = matrix1[i][j];
		}
	}

	
	
	//multiply 	
//	printf("\n");
//	printf("multiply\n");
//	multiply(matrixTA,include1s,rows,aug,rows,include1s);
	multiply(matrix1T,include1s,rows,matrix1,rows,include1s);	
//	print(mult,include1s,include1s);
//----------------------------------------------------------------------
	//printinf everything else; 
	
//	printf("MatrixY\n");
//	print(matrixY,rows,columns+1);
//	printf("matrix without N \n");
//	print(matrix,rows,columns);
//	printf("\n");
//	printf("Transpose\n");
//	print(matrixTA,include1s,rows);
//	printf("with1s:\n");
//	print(matrix1,rows,include1s);
//	printf("transpose1s:\n");
//	print(matrix1T,include1s,rows);
//	printf("mult\n");
//	print(mult,include1s,include1s);	
 	// inverse
//	printf("inverse:\n"); 
	inverse(mult,include1s);

	multiply(inverse1,include1s,include1s,matrix1T,include1s,rows);
//	printf("multiply by transpose\n");
//	printf("\n");
//	print(mult,include1s,rows);

	//vector y;
	double ** vectory; 
	//memory allocation 
	//printf("%d\n",columns);
	//printf("%d\n",rows);
	vectory= malloc(rows*sizeof(double*));
	for(i=0;i<rows;i++){
		vectory[i] = malloc(1*sizeof(double*));
	}
	// fill 
	for(i=0;i<rows;i++){
		for(j=0;j<1;j++){
			vectory[i][j] = matrixY[i][columns];
			}
		}
//	print(vectory,rows,1);
//----------------------------------------------------------------------------------
//	printf("\n");
	multiply(mult,include1s,rows,vectory,rows,1);	
//	print(mult,columns+1,1);
//----------------------------------------------------------------------------------
 // second file 
 //	int count;
	// count =0;  
	FILE *file2; 
	file2 = fopen(argv[2],"r");
	int rowX;
//	printf("\n"); 
	fscanf(file2,"%d\n",&rowX);
	//printf("rowX:%d\n",rowX);
	//printf("columns:%d\n",columns);
	double** test;
	test = malloc(rowX * sizeof(double*));
	//malloc
	for(i=0;i<rowX;i++){
	test[i]= malloc((columns)*sizeof(double));
	}
	//fill 
	for(i=0;i<rowX;i++){
		for(j=0;j<columns;j++){
		fscanf(file2,"%lf,",&test[i][j]);
		}
	}
//	print(test,rowX,columns);
//-----------------------------------------------------------------------------------
	// applying weights to formula 
		double cost = 0;
	for(i=0; i<rowX; i++){
		cost=mult[0][0];
			for(j=1; j<columns; j++){
			cost = cost +mult[j][0] * test[i][j-1];	
			}
	printf("%0.0lf\n",cost);
	}
	
	return 0;
}

