#include "register_types.h"
#include "core/class_db.h"
#include "scale.h"

void register_scale_types(){
	ClassDB::register_class<Scale>();
}

void unregister_scale_types() {
}
