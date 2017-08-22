#pragma once
#include "event_structure.h"
void init_event(event_function sto_event_func[], event_function seq_event_func[], event_function spe_event_func[]);
int trigger_sequencial_event(int month, whatDay day_of_week, int week, event_function event_func[]);
int trigger_stochastic_event(event_function sto_event_func[], float *prob_store);