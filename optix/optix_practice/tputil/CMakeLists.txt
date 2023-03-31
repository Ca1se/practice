file(GLOB TPUTIL_SRCS
	*.cpp
	*.h
)

add_library(tputil
	${TPUTIL_SRCS}
)

set_target_properties(tputil PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
)

target_include_directories(tputil PUBLIC
    ${CUDAToolkit_INCLUDE}
	${OptiX_INCLUDE}
)

target_link_libraries(tputil PUBLIC
	${OptiX_LIBRARIES}
	CUDA::cudart
	CUDA::cuda_driver
	glad
	glfw3
)