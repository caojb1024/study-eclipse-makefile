#
# 需要生成的文件
TARGS +=  bin/ace_socket_base
# 静态库文件名  -l -lACE		 
LIBS := ACE           
# 静态库目录    -L -L/usr/local/ACE/lib 
LIBPATHS:= /usr/local/ACE/lib              
# 头文件目录    -I -I/usr/local/ACE/include    
INCS:= /usr/local/ACE/include
# 其他的源代码
SRCDIR:=              

all: $(TARGS)


bin/%: ../../../comm/ace/src/%.o
	g++ -o ../../../$(@) $(^) $(addprefix -l,$(LIBS)) $(addprefix -L,$(LIBPATHS))
	@echo ''
%.o: %.cpp
	g++ -c -o $(@) $(^) -g -Wall $(addprefix -I,$(INCS))

.PNONY: all clean

clean:
	-rm -rf $(TARGS) *.o