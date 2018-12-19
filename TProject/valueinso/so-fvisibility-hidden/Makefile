cc=g++ 
stdflag= -std=c++11 -fvisibility=hidden 

logfile = bin/*.txt bin/*.log

progp1=bin/p1
progp2=bin/p2
tso1=bin/libtso1.so
tso2=bin/libtso2.so

inc_path= -I./tso1 -I./tso2
lib_path= -L./bin
link= -ltso1 -ltso2 -lpthread 
solinkflag= -fPIC -shared 
deps=$(shell find ./ -name "*.h") 

p1src=$(shell find ./p1WR/ -name "*.cpp")
p1obj=$(p1src:%.cpp=%.o)

p2src=$(shell find ./p2OR/ -name "*.cpp")
p2obj=$(p2src:%.cpp=%.o)

tso1src=$(shell find ./tso1/ -name "*.cpp")
tso1obj=$(tso1src:%.cpp=%.o)

tso2src=$(shell find ./tso2/ -name "*.cpp")
tso2obj=$(tso2src:%.cpp=%.o)

#if no all, only link p1
.PHONY : all
all:$(progp1) $(progp2)

$(progp1):$(p1obj) $(tso1) $(tso2)
	@echo "--->start link" $(progp1) "......"
	@echo $(cc) $(p1obj) $(stdflag) $(lib_path) $(link) -o $(progp1)
	@$(cc) $(p1obj) $(stdflag) $(lib_path) $(link) -o $(progp1)
	@echo " "

$(p1obj):$(p1src) $(deps)
	@echo "--->start compile" $(p1obj) "......"
	@echo $(cc) $(stdflag) $(inc_path) -c $< -o $@
	@$(cc) $(stdflag) $(inc_path) -c $< -o $@
	@echo " "

$(tso1):$(tso1obj)
	@echo "--->start link" $(tso1) "......"
	@echo $(cc) $(stdflag) $(tso1obj) $(solinkflag) $(inc_path) -o $(tso1)
	@$(cc) $(stdflag) $(tso1obj) $(solinkflag) $(inc_path) -o $(tso1)
	@echo " "

$(tso1obj):$(tso1src) $(deps)
	@echo "--->start compile" $(tso1obj) "......"
	@echo $(cc) $(stdflag) $(solinkflag) $(inc_path) -c $< -o $@
	@$(cc) $(stdflag) $(solinkflag) $(inc_path) -c $< -o $@
	@echo " "

$(tso2):$(tso2obj)
	@echo "--->start link" $(tso2) "......"
	@echo $(cc) $(stdflag) $(tso2obj) $(solinkflag) $(inc_path) -o $(tso2)
	@$(cc) $(stdflag) $(tso2obj) $(solinkflag) $(inc_path) -o $(tso2)
	@echo " "

$(tso2obj):$(tso2src) $(deps)
	@echo "--->start compile" $(tso2obj) "......"
	@echo $(cc) $(stdflag) $(solinkflag) $(inc_path) -c $< -o $@
	@$(cc) $(stdflag) $(solinkflag) $(inc_path) -c $< -o $@
	@echo " "

$(progp2):$(p2obj) $(tso1) $(tso2)
	@echo "--->start link" $(progp2) "......"
	@echo $(cc) $(p2obj) $(stdflag) $(lib_path) $(link) -o $(progp2)
	@$(cc) $(p2obj) $(stdflag) $(lib_path) $(link) -o $(progp2)
	@echo " "

$(p2obj):$(p2src) $(deps)
	@echo "--->start compile" $(p2obj) "......"
	@echo $(cc) $(stdflag) $(inc_path) -c $< -o $@
	@$(cc) $(stdflag) $(inc_path) -c $< -o $@
	@echo " "

.PHONY : clean
clean:
	@echo "--->start clean......"
	@echo rm -rf $(progp1) $(p1obj) $(progp2) $(p2obj) $(tso1) $(tso1obj) $(tso2) $(tso2obj) $(logfile)
	@rm -rf $(progp1) $(p1obj) $(progp2) $(p2obj) $(tso1) $(tso1obj) $(tso2) $(tso2obj) $(logfile)
	@echo " "


