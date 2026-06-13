#include <time.h>
#include <stdint.h>
#include "../include/snowflake_id.h"
#include <stdlib.h>

Snowflake_id_generator_t* snowflake_id_generator_new(uint64_t epoch, uint_t instance){
Snowflake_id_generator_t* g = (Snowflake_id_generator_t*)malloc(sizeof(Snowflake_id_generator_t));
    if(g == NULL) return g;
    g->epoch = epoch;
    g->instance = instance;
    g->seq = 0;
    g->last_ts = 0;
    return g;
}

void snowflake_id_generator_free(Snowflake_id_generator_t* g) {
  if (g != NULL) free(g);
}


snowflake_id_t snowflake_id_generate(Snowflake_id_generator_t* g) {
  struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    snowflake_id_t id = 0;
    int64_t timestamp_ms =
        (int64_t)ts.tv_sec * 1000LL + ts.tv_nsec / 1000000;
  if(g->epoch != 0) {
    timestamp_ms -= g->epoch;
  }

  if (g->last_ts == timestamp_ms) {
    g->seq += 1;
  } else {
    g->seq = 0;
  }
  g->last_ts = timestamp_ms;

    id |= timestamp_ms << 22;
    id |= g->instance << 12;
    id |= g->seq;
  return id;
}


Snowflake_id_info_t* snowflake_id_get_info(snowflake_id_t id){
  uint64_t timestamp = (id >> 22);
  uint64_t instance = (id << 42) >> 54;
  uint64_t sequence = (id << 52) >> 52;
  Snowflake_id_info_t* i = (Snowflake_id_info_t*)malloc(sizeof(Snowflake_id_info_t));
  if(i == NULL) return i;
  i->timestamp = timestamp;
  i->instance = instance;
  i->sequence = sequence;
  return i;
}

void snowflake_id_info_free(Snowflake_id_info_t* i){
  if(i != NULL) free(i);
}
