#ifndef _H_PICTURE_FRAME_
#define _H_PICTURE_FRAME_

#include <stdarg.h>

// Configuration
// TODO move to configuration file.


#define FIELD_NAME_MAX_SIZE 10
#define SIMPLE_TYPE_MAX_SIZE 15





typedef enum {
	NO_TYPE,
	STRING,
	NUMBER,
	BOOLEAN,
	NULL_VALUE
} Simple_Value_Type;

typedef enum {
	DOCUMENT = 5,
	ARRAY
} Complex_Value_Type;

typedef enum {
	INVALID,
	VALID
}Validity;

struct Simple_Value{
	Simple_Value_Type type;
	Validity valid;
	void* (*capture)(void);
	char value[SIMPLE_TYPE_MAX_SIZE];

};

struct Complex_Value{
	Complex_Value_Type type;
	Validity valid;
	void* (*capture)(void*);
	void* negative;
	int negativeSize;
};

struct Generic_value{
	int type;
	Validity valid;
	void* (*capture)(void*);
};

union Value{
	char type;
	struct Simple_Value simpleValue;
	struct Complex_Value complexValue;
	struct Generic_value genericValue;
};

struct Field{
	char name[FIELD_NAME_MAX_SIZE];
	union Value value;
};

typedef struct Field* Negative;

void __insert_fields(Negative negative, int fieldNumber, char* va_args);
void __insert_types(Negative negative, int typesNumber, ...);

void __insert_captures(Negative negative, int captureNumber, ...);
void develop(Negative negative, void* paper, int size, char* name);
void capture(Negative negative, int size);

#define DECLARE_FIELDS(X, ...)\
\
enum {__VA_ARGS__ , X##_FIELD_TOTALS};\
struct Field X##_Fields[X##_FIELD_TOTALS];\
Negative X = X##_Fields;\
__insert_fields(X, X##_FIELD_TOTALS, #__VA_ARGS__);

#define DECLARE_TYPES(X, ...) __insert_types(X, X##_FIELD_TOTALS, __VA_ARGS__);
#define DECLARE_CAPTURES(X, ...) __insert_captures(X, X##_FIELD_TOTALS, __VA_ARGS__);


#endif
