set(CudaSystemSrc
	${PROJECT_SOURCE_DIR}/src/MnSystem/Cuda/Cuda.cu
	${PROJECT_SOURCE_DIR}/src/MnSystem/Cuda/DeviceUtils.cu
	${PROJECT_SOURCE_DIR}/src/MnSystem/Cuda/MemoryUtils.cu
)

# SET(LOCAL_PROJECT_NAME "Apple")
# file(GLOB_RECURSE srcs CONFIGURE_DEPENDS *.cpp *.h)
# add_library(${LOCAL_PROJECT_NAME} STATIC ${srcs})


# build: PRIVATE, usage: INTERFACE, both: PUBLIC.
# if (USE_CUDA_COMPILER)
	add_library(mncuda)
	
	target_include_directories(mncuda
		PUBLIC ${PROJECT_SOURCE_DIR}/src
		${PROJECT_SOURCE_DIR}/src/Depends
	)
	
	target_sources(mncuda
		PRIVATE	${CudaSystemSrc}
	)
	
	# target_precompile_headers(mncuda 
	# 	INTERFACE	Cuda/Cuda.h
	# 				Cuda/DeviceUtils.cuh
	# 				Cuda/HostUtils.hpp
	# )

# endif()