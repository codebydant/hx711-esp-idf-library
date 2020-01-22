set(srcs "main.c"

		 "include/HX711.c"
		 "include/hx711_lib.c"
		 )

idf_component_register(SRCS ${srcs} INCLUDE_DIRS ".")




