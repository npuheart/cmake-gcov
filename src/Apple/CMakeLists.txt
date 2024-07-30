
SET(LOCAL_PROJECT_NAME "Apple")
file(GLOB_RECURSE srcs CONFIGURE_DEPENDS *.cpp *.h)
add_library(${LOCAL_PROJECT_NAME} STATIC ${srcs})

# 关于头文件的引入
# 外部文件夹只能通过 #include <Apple/xxx.h> 的方式引入
# 内部文件夹可以通过 #include "xxx.h" 的方式引入
