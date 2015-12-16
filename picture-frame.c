#include "picture-frame.h"

#include <string.h>
#include <stdarg.h>
//#include "json-builder.h"
#include "config.h"


void __insert_fields(Negative negative, int fieldNumber, char* va_args){
	int i;
	char* token;
	char va_args_buffer[VA_ARGS_BUFFFERSIZE];

	memcpy(va_args_buffer, va_args, strlen(va_args));
	token = strtok(va_args_buffer, ", ");

	for(i = 0; i < fieldNumber; i++){
		memcpy(negative[i].name, token, strlen(token) + 1);
		negative[i].value.genericValue.capture = NULL;
		negative[i].value.genericValue.type = NO_TYPE;
		negative[i].value.genericValue.valid = INVALID;
		token = strtok(NULL, ", ");
		if(!token) return;
	}
}

void __insert_types(Negative negative, int typesNumber, ...){
	va_list list;
	int i;

	va_start(list, typesNumber);
	for(i = 0; i < typesNumber; i++){
		negative[i].value.type = va_arg(list, int);
	}
	va_end(list);

}

void __insert_captures(Negative negative, int captureNumber, ...){
	va_list list;
	int i;

	va_start(list, captureNumber);
	for(i = 0; i < captureNumber; i++){
		negative[i].value.genericValue.capture = va_arg(list, void*);
	}
	va_end(list);
}

void capture(Negative negative, int size){
	int i;
	int j;
	char* capturedString;

	for(i = 0; i < size; i++){
		switch(negative[i].value.type){
		case NO_TYPE:
			break;
		case STRING:
			capturedString = negative[i].value.simpleValue.capture();
			memcpy(negative[i].value.simpleValue.value, capturedString, strlen(capturedString));
			negative[i].value.simpleValue.valid = VALID;
			break;
		case NUMBER:
			capturedString = negative[i].value.simpleValue.capture();
			memcpy(negative[i].value.simpleValue.value, capturedString, strlen(capturedString));
			negative[i].value.simpleValue.valid = VALID;
			break;
		case BOOLEAN:
			capturedString = negative[i].value.simpleValue.capture();
			memcpy(negative[i].value.simpleValue.value, capturedString, strlen(capturedString));
			negative[i].value.simpleValue.valid = VALID;
			break;

		case DOCUMENT:
			for(j = 0; i < negative[i].value.complexValue.negativeSize; j++){
				if(((Negative)(negative[i].value.complexValue.negative))->value.genericValue.valid != VALID){
					negative[i].value.complexValue.valid = INVALID;
					break;
				}
			}
			negative[i].value.complexValue.valid = VALID;
			break;
		case ARRAY:
			for(j = 0; i < negative[i].value.complexValue.negativeSize; j++){
				if(((Negative)(negative[i].value.complexValue.negative))->value.genericValue.valid != VALID){
					negative[i].value.complexValue.valid = INVALID;
					break;
				}
			}
			negative[i].value.complexValue.valid = VALID;
			break;
		default:
			break;
		}
	}
}
/*
void develop(Negative negative, void* paper, int size, char* name){
		int i;

		Serialized_Document* document = (Serialized_Document*)paper;

		startNewDocument(document, name);


		for(i = 0; i < size; i++){
			switch (negative[i].value.genericValue.type){
			case STRING:
				insertString(document, negative[i].name, negative[i].value.simpleValue.value);
				negative[i].value.simpleValue.valid = INVALID;
			break;
			case NUMBER:
				insertNumber(document, negative[i].name, negative[i].value.simpleValue.value);
				negative[i].value.simpleValue.valid = INVALID;
				break;
			case BOOLEAN:
				if(strstr(negative[i].value.simpleValue.value, "true") == 0) insertTrue(document, negative[i].name);
				if(strstr(negative[i].value.simpleValue.value, "false") == 0) insertFalse(document, negative[i].name);
				negative[i].value.simpleValue.valid = INVALID;
				break;
			case NULL_VALUE:
				if(strstr(negative[i].value.simpleValue.value, "true") == 0) insertTrue(document, negative[i].name);
				if(strstr(negative[i].value.simpleValue.value, "false") == 0)insertFalse(document, negative[i].name);
				negative[i].value.simpleValue.valid = INVALID;
				break;
#ifdef USE_RECURSIVE_DEVELOPMENT
			case DOCUMENT:
				develop(negative[i].value.complexValue.negative, document, negative[i].value.complexValue.negativeSize, negative[i].name);
			break;
			case ARRAY:
				break;
			default:
				break;
#endif
			}
		}
}*/
