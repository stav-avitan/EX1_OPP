#include <stdlib.h>
#include "AdptArray.h"
//The AdptArray struct is composed of three main components: the size of the array, a pointer to the elements of the array, and three functions that operate on the elements. The first function is responsible for copying elements, the second function is responsible for deleting elements, and the third function is responsible for printing elements.
typedef struct AdptArray_ {
	PElement* Pelements;
	int len;
	COPY_FUNC copyFunc;
    	DEL_FUNC delFunc;
    	PRINT_FUNC printFunc;
}AdptArray;

//The function "CreateAdptArray" creates a new array by accepting three functions as parameters: "copyFunc", "delFunc", and "printFunc". The function returns a pointer to the newly created array.
PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc, PRINT_FUNC printFunc) {
	//Allocates memory for the array using the "malloc" function and stores the pointer to the allocated memory in a variable named "arr"
    	PAdptArray arr = malloc(sizeof(*arr));
    	if (arr == NULL) {
        	return NULL;
    	}
    	//Initialize the variables and functions of the array
    	arr->len = 0;
    	arr->copyFunc = copyFunc;
    	arr->delFunc = delFunc;
    	arr->printFunc = printFunc;
    	arr->Pelements = NULL;
    	return arr;
}
//The function "DeleteAdptArray" deletes an array and its elements. The function accepts a pointer to the array that needs to be deleted as a parameter.
void DeleteAdptArray(PAdptArray arr) {
    	if (arr == NULL) {
        	return;
    	}

    	int i = 0;
    	//Iterate over all the elements in the array using a "while" loop. For each element that is not NULL, the function uses the "delFunc" function to delete it.
    	while (i < arr->len) {
        	if (arr->Pelements[i] != NULL) {
            	arr->delFunc(arr->Pelements[i]);
        	}
        	i++;
    	}
	//Release the memory allocated for the array elements using the "free" function
    	free(arr->Pelements);
    	arr->Pelements = NULL;
    	//Releases the memory allocated for the array itself using the "free" function
    	free(arr);
    	arr = NULL;
}
//The function "SetAdptArrayAt" changes the element at a specified index in the array to a new element provided by the user. The function returns a Result value indicating whether the operation was successful or not.
Result SetAdptArrayAt(PAdptArray arr, int idx, PElement element) {
    	if (arr == NULL) {
        	return FAIL;
    	}

    	if (idx < 0) {
        	return FAIL;
    	}
	//If the index is greater than or equal to the current size of the array, the function resizes the array by creating a new pointer to the elements using the "realloc" function.
    	if (idx >= arr->len) {
        	PElement* new_Pelements = (PElement*)realloc(arr->Pelements, (idx + 1) * sizeof(PElement));
		//The new pointer has enough memory to store the new element at the specified index. The function initializes any new elements with NULL and updates the size of the array accordingly.
        	if (new_Pelements == NULL) {
            	return FAIL;
        	}

        	for (int i = arr->len; i <= idx; i++) {
            	new_Pelements[i] = NULL;
        	}

        	arr->Pelements = new_Pelements;
        	arr->len = idx + 1;
        //If there is an existing element at the specified index, the function uses the "delFunc" function to delete it.
    	} else if (arr->Pelements[idx] != NULL) {
        	arr->delFunc(arr->Pelements[idx]);
    	}
	//Copy the new element to the index by using the "copyFunc" function and returns a SUCCESS.
    	arr->Pelements[idx] = arr->copyFunc(element);
    	return SUCCESS;
}

//The function "GetAdptArrayAt" returns a copy of the element at the specified index in the array.
PElement GetAdptArrayAt(PAdptArray arr, int idx) {

    	if (arr == NULL || arr->Pelements[idx] == NULL || idx >= arr->len || idx < 0) { return NULL; }

    	return arr->copyFunc(arr->Pelements[idx]);
}
//The function "GetAdptArraySize" returns the size of the array.
int GetAdptArraySize(PAdptArray arr) {

    	if (arr != NULL) {
        	return arr->len;
    	}

    	return -1;
}
//The function "PrintDB" prints the elements in the array.
void PrintDB(PAdptArray arr) {
    	if (arr == NULL) {
        	return;
    	}
	//Create a pointer to pointers 
    	void** ptr = arr->Pelements;
    	int len = arr->len;
    	while (len--) {
        	if (*ptr != NULL) {
        	    	arr->printFunc(*ptr);
            		printf("\n");
        	}
        	ptr++;
    }
}
