//handles simple integrals by finding the variable and getting it's constant and exponent.
//2x^6 or 1x + 6x + 6x^6 + 6

#include<bits/stdc++.h>
using namespace std;

int constantsTemp[100];
int constantsBefVar[100];
int exponents[100];
int temp[100];
int orderOfMagnitude = 1;
int num = 0;
int countConstantPart = 0;
bool expon = false;
bool cons = false;
char placeholder = 'x';
char signs[100];
string equation;

int sizeArray(int array[]){
	num = 0;
	while(array[num] != -1){
		num++;
	}
	return num;
}

int sizeArray(char array[]){
	num = 0;
	while(array[num] != -1){
		num++;
	}
	return num;
}

void clearArray(int array[], int setTo){
	for(int i = 0; i < 100; i++){
		array[i] = setTo;
	}
}

void clearArray(char array[], char setTo){
	for(int i = 0; i < 100; i++){
		array[i] = setTo;
	}
}

void printArray(int array[], int sizeOfArray){
	cout << "int array start (size: " << sizeArray(array) << ")" << endl;
	for(int i = 0; i < sizeOfArray; i++){
		cout << "i: " << i << " v: " << array[i] << endl;
	}
	cout << "int array end" << endl;
}

void printArray(char array[], int sizeOfArray){
	cout << "char array start (size: " << sizeArray(array) << ")" << endl;
	for(int i = 0; i < sizeOfArray; i++){
		cout << "i: " << i << " ch: " << array[i] << endl;
	}
	cout << "char array end" << endl;
}

//a constant multiplied by x or y
void constantMulti(char equationAr[], int index, int& constBefVarCount, int count){

	//store values in constantsTemp
	if(equation[index] != ' '){
		constantsTemp[countConstantPart] = equationAr[index] - '0';
		countConstantPart++;
	}
	//if the whole constant has been found
	if(equation[index] == ' ' || index == 0){
		//add all the integers together but increase the order of magnitude
		count = 0;
		while(constantsTemp[count] != -1){
			constantsBefVar[constBefVarCount] += (constantsTemp[count] * orderOfMagnitude);
			//cout << constantsBefVar[constBefVarCount] << " add the following " << (constantsTemp[count] * orderOfMagnitude) << endl;
			orderOfMagnitude *= 10;
			count++;
		}
		count = 0;
		orderOfMagnitude = 1;
		constBefVarCount++;
		countConstantPart = 0;
	}
}

void exponentManager(char equationAr[], int index, int& exponentCount, int count){

	//store values in constantsTemp
	constantsTemp[countConstantPart] = equationAr[index] - '0';
	countConstantPart++;
	
	//if the whole exponent has been found
	if(equationAr[index+1] == 'q' || equationAr[index+1] == ' '){
		countConstantPart--;
		//cout << "end of file found " << constantsTemp[countConstantPart] << " " << countConstantPart << endl;
		//add all the integers together but increase the order of magnitude
		//count = 0;
		for(int i = countConstantPart+1; i > 0; i--){
			exponents[exponentCount] += (constantsTemp[countConstantPart] * orderOfMagnitude);
			//cout << exponents[exponentCount] << " exponent add the following " << (constantsTemp[countConstantPart] * orderOfMagnitude) << endl;
			orderOfMagnitude *= 10;
			countConstantPart--;
		}
		count = 0;
		orderOfMagnitude = 1;
		exponentCount++;
		countConstantPart = 0;
	}
}

void solveIntegralPC(int constant, char placeholder){
	cout << "solveIntegralPC" << endl;
	num = 2;
	//divide num from whole answer
	cout << "(" << constant << placeholder << "^" << num << ")/" << num << " ";
}

void solveIntegralPE(int exponent, char placeholder){
	cout << "solveIntegralPE" << endl;
	num = 0;
	exponent += 1;
	num = exponent;
	//divide num from whole answer
	cout << "(" << placeholder << "^" << exponent << ")/" << num << " ";
}

void solveIntegralP(char placeholder){
	cout << "solveIntegralP" << endl;
	num = 2;
	//divide num from whole answer
	cout << "(" << placeholder << "^" << num << ")/" << num << " ";
}

void solveIntegralC(int constant){
	cout << "solveIntegralC" << endl;
	num = 0;
	//exponent++;
	//num = exponent;
	//divide num from whole answer
	cout << constant << "x "; 
}

void solveIntegralPEC(int constant, int exponent, char placeholder){
	//keeps calling this instead of other functions
	cout << "solveIntegralPEC" << endl;
	num = 0;
	exponent++;
	num = exponent;
	//divide num from whole answer
	cout << "(" << constant << "x^" << exponent << ")/" << num << " ";
}

void checkTerm(int terms, int& integralType){
	//also in the event of a lone constant
	if(constantsBefVar[terms] != 0){
		cons = true;
	}
	printArray(exponents, 10);
	if(exponents[terms] != 0){
		expon = true;
	}
	//classify the term
	if(cons == false && expon == false){
		integralType = 1;
		//cout << "Is type " << 1 << endl;
	}
	if(cons == true && expon == false){
		integralType = 2;
		//cout << "Is type " << 2 << endl;
	}
	if(cons == false && expon == true){
		integralType = 3;
		//cout << "Is type " << 3 << endl;
	}
	if(cons == true && expon == true){
		integralType = 4;
		//cout << "Is type " << 4 << endl;
	}
	expon = false;
	cons = false;
}

void assignAndSend(int integralType, int& constantCountSolv, int& exponentCountSolv, int& signCount){
	//given these integral types, get the proper values and call the proper function:
	//prints an integral
	switch(integralType){
		case 1: solveIntegralP(placeholder); break;
		case 2: solveIntegralPC(constantsBefVar[constantCountSolv], placeholder);
				constantCountSolv++; break;
		case 3: solveIntegralPE(exponents[exponentCountSolv], placeholder);
				exponentCountSolv++; break;
		case 4: solveIntegralPEC(constantsBefVar[constantCountSolv], exponents[exponentCountSolv], placeholder);
				constantCountSolv++;
				exponentCountSolv++; break;
		default: cout << "I could not understand one of the terms.";
	}
	//prints a sign
	if(signs[signCount] != '0'){
		cout << signs[signCount] << " ";
	}
	signCount++;
}

int main(){
	char equationAr[100];
	int index = 0, constant = 0;
	int constantCount = 0, exponentCount = 0;
	int constantCountSolv = 0, exponentCountSolv = 0;
	int constBefVarCount = 0;
	int signCount = 0;
	int count = 0;
	int terms = 0;
	int integralType = 0;
	
	clearArray(equationAr, 'q');
	clearArray(constantsTemp, -1);
	clearArray(temp, -1);
	clearArray(constantsBefVar, 0);
	clearArray(exponents, 0);
	clearArray(signs, '0');
	
	//get index in the string of all plus and minuses (the sign's index dictates the term's index)
	for(int i = 0; i < equation.length(); i++){
		if(equation[i] == '+'){
			signs[signCount] = '+';
			signCount++;
		}
		if(equation[i] == '-'){
			signs[signCount] = '-';
			signCount++;
		}
	}
	
    cout << "Please input the equation in this format: 2x^6 or 1x + 6x + 6x^6" << endl;
    getline(cin, equation);
	
	//Problem: equation does not contain 
    for(int i = 0; i < equation.length(); i++){
        equationAr[i] = equation[i];
		//cout << equationAr[i] << endl;
    }
	
	for(int i = 0; i < equation.length(); i++){
		//cout << i << " " << equation << endl;
		if(equationAr[i] == 'x' || equationAr[i] == 'y'){
			//cout << "an x or y has been located" << endl;
			//CONSTANTS multiplied by a variable back track from the x discovered and get the constant up to a whitespace. (i is location of a var)
			clearArray(constantsTemp, -1);
			for(int j = 1; j < equation.length(); j++){
				index = i-j;
				//cout << "all indexs: " << index << " i: " << i << " - " << j << endl;
				//weird debugging. Why's index negative?
				if(index > -1){
					//cout << "accepted index: " << index << endl;
					constantMulti(equationAr, index, constBefVarCount, count);
					if(equationAr[i-j] == ' '){
						//cout << "found a whitespace" << endl;
						break;
					}
				}
			}
			countConstantPart = 0;
			count = 0;
			//EXPONENTS increment forward until a whitespace is found getting the exponent
			clearArray(constantsTemp, -1);
			if(equationAr[i+1] == '^'){
				//cout << "^ has been found" << endl;
				for(int j = 1; j < equation.length(); j++){
					index = i+j+1;
					if(equationAr[i+j+1] == ' ' || equationAr[index] == 'q'){
						//cout << "exponent index is whitespace" << endl;
						break;
					}
				exponentManager(equationAr, index, exponentCount, count);
				}
			countConstantPart = 0;
			count = 0;
			}
			//This is reading in the wrong thing for each term. You will have to find the bools while you are getting the exponent/const , then get the Integral type and clear them when down here.
			checkTerm(terms, integralType);
			assignAndSend(integralType, constantCountSolv, exponentCountSolv, signCount);
		}
	}
	//get total number of terms
	for(int i = 0; i < equation.length(); i++){
		if(equation[i] == 'x' || equation[i] == 'y'){
			terms++;
			//cout << terms << endl;
		}
	}
	cout << "+ C";
	//cout << constantsBefVar[0] << "x^" << exponents[0] << " " << constantsBefVar[1] << "x^" << exponents[1];
}