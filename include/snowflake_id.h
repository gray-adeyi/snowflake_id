#ifndef SNOWFLAKE_ID_H
#define SNOWFLAKE_ID_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// A representation of a snowflake ID
typedef uint64_t snowflake_id_t;


// This is the generator used to create the
// snowflake ID, it should be instantiated with
// `snowflake_id_generator_new`
typedef struct snowflake_id_generator {
  uint64_t last_ts;
  uint_t seq;
  uint64_t epoch;
  uint_t instance;
} Snowflake_id_generator_t;

// A representation to provide information on the 
// parts that make up a snowflake ID
typedef struct snowflake_id_info {
  uint64_t timestamp;
  uint_t instance;
  uint_t sequence;
} Snowflake_id_info_t;

// Creates a new instance of the snowflake_id_generator,
// the epoch param should be 0 to use the Unix Epoch, 
// machine_id can be any number from 0-1023
Snowflake_id_generator_t* snowflake_id_generator_new(uint64_t epoch, uint_t machine_id);

// Free a generator from memory
void snowflake_id_generator_free(Snowflake_id_generator_t* g);

// Uses the snowflake_id_generator to generate a snowflake ID 
snowflake_id_t snowflake_id_generate(Snowflake_id_generator_t* g);

// Retrieves the info on the parts that make up a snowflake ID
Snowflake_id_info_t* snowflake_id_get_info(snowflake_id_t id);

// Free the memory used by an info
void snowflake_id_info_free(Snowflake_id_info_t* i);

#ifdef __cplusplus
}
#endif

#endif /* SNOWFLAKE_ID_H */
