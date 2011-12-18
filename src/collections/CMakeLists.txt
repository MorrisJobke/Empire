# adding libraries
# parameter:
#	library cmake name
#	source name
add_library(Collection Collection)
add_library(Collectionlist Collectionlist)
set_target_properties(Collectionlist PROPERTIES LINKER_LANGUAGE C)
add_library(Propertylist Propertylist)
set_target_properties(Propertylist PROPERTIES LINKER_LANGUAGE C)