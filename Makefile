#
# 需要生成的文件
TARGS +=  bin/simple_http_server \
          bin/simple_http_client \
          bin/ace_task_msgblock \
          bin/ace_task_threadmanager \
          bin/ace_mul_echo_server \
          bin/ace_produce_consumer \
          bin/ace_sap_dgram_echoserver \
          bin/ace_sap_dgram_echosclient \
          
          
          
# 静态库文件名  -l -lACE		 
LIBS := ACE pthread          
# 静态库目录    -L -L/home/bingcod/libs/ACE/lib 
LIBPATHS:= /home/bingcod/libs/ACE/lib              
# 头文件目录    -I -I/home/bingcod/libs/ACE/include    
INCS:= /home/bingcod/libs/ACE/include
# 其他的源代码
SRCDIR:=              

all: $(TARGS)

bin/%: %.o
	g++ -o $(@) $(^) $(addprefix -l,$(LIBS)) $(addprefix -L,$(LIBPATHS))
	@echo ''
%.o: %.cpp
	g++ -c -o $(@) $(^) -g -Wall $(addprefix -I,$(INCS))

.PNONY: all clean

clean:
	-rm -rf $(TARGS) *.o