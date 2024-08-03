SET(LOCAL_PROJECT_NAME "mncuda")

set(srcs
	${PROJECT_SOURCE_DIR}/src/Mn/MnSystem/Cuda/Cuda.cu
	${PROJECT_SOURCE_DIR}/src/Mn/MnSystem/Cuda/DeviceUtils.cu
	${PROJECT_SOURCE_DIR}/src/Mn/MnSystem/Cuda/MemoryUtils.cu
)

# build: PRIVATE, usage: INTERFACE, both: PUBLIC.
# if (USE_CUDA_COMPILER)
	add_library(${LOCAL_PROJECT_NAME})
	
	target_include_directories(${LOCAL_PROJECT_NAME}
		PUBLIC 
		${PROJECT_SOURCE_DIR}/src/Mn
		${PROJECT_SOURCE_DIR}/src/Depends
	)
	
	target_sources(${LOCAL_PROJECT_NAME}
		PRIVATE	${srcs}
	)
	
	# target_precompile_headers(mncuda 
	# 	INTERFACE	Cuda/Cuda.h
	# 				Cuda/DeviceUtils.cuh
	# 				Cuda/HostUtils.hpp
	# )

# endif()