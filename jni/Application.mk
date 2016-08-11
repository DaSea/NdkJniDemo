# The ARMv7 is significanly faster due to the use of the hardware FPU
# 使用GCC4.7  
NDK_TOOLCHAIN_VERSION := 4.6
#APP_ABI := armeabi-v7a armeabi
#只生成rmeabi-v7a架构的CPU用的lib，要生成所有平台的可以改为all   
APP_ABI := all
APP_PLATFORM := android-14
APP_STL := gnustl_static
# APP_STL := gnustl_shared
#允许异常功能，及运行时类型识别  
APP_CPPFLAGS += -fexceptions -frtti 
 #此项有效时表示宽松的编译形式，比如没有用到的代码中有错误也可以通过编译；使用GNU STL时不用此项std::string 居然编译不通过！
# APP_CPPFLAGS +=-fpermissive 