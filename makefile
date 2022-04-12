BuiltD:= $(wildcard Built_in_Commands/*.c)
BuiltDO:= $(addprefix Object_Files/, $(notdir $(addsuffix .o,$(basename $(BuiltD)))))
BuiltOD = $(addprefix Built_in_Commands/,$(notdir $(addsuffix .c,$(basename $@))))

ParentD := $(wildcard *.c)
ParentDO:= $(addprefix Object_Files/,$(addsuffix .o,$(basename $(ParentD))))
ParentOD = $(notdir $(addsuffix .c,$(basename $@)))

SystemD := $(wildcard System_Commands/*.c)
SystemDO:= $(addprefix Object_Files/, $(notdir $(addsuffix .o,$(basename $(SystemD)))))
SystemOD = $(addprefix System_Commands/,$(notdir $(addsuffix .c,$(basename $@))))

PromptD := $(wildcard Prompt/*.c)
PromptDO:= $(addprefix Object_Files/, $(notdir $(addsuffix .o,$(basename $(PromptD)))))
PromptOD = $(addprefix Prompt/,$(notdir $(addsuffix .c,$(basename $@))))

ManagerD := $(wildcard Managers/*.c)
ManagerDO:= $(addprefix Object_Files/, $(notdir $(addsuffix .o,$(basename $(ManagerD)))))
ManagerOD = $(addprefix Managers/,$(notdir $(addsuffix .c,$(basename $@))))

DataabsD := $(wildcard Data_Abstractions/*.c)
DataabsDO:= $(addprefix Object_Files/, $(notdir $(addsuffix .o,$(basename $(DataabsD)))))
DataabsOD = $(addprefix Data_Abstractions/,$(notdir $(addsuffix .c,$(basename $@))))

TopD := $(wildcard Top_Execute/*.c)
TopDO:= $(addprefix Object_Files/, $(notdir $(addsuffix .o,$(basename $(TopD)))))
TopOD = $(addprefix Top_Execute/,$(notdir $(addsuffix .c,$(basename $@))))

InputD := $(wildcard Input/*.c)
InputDO:= $(addprefix Object_Files/, $(notdir $(addsuffix .o,$(basename $(InputD)))))
InputOD = $(addprefix Input/,$(notdir $(addsuffix .c,$(basename $@))))

SignalD := $(wildcard Signals/*.c)
SignalDO:= $(addprefix Object_Files/, $(notdir $(addsuffix .o,$(basename $(SignalD)))))
SignalOD = $(addprefix Signals/,$(notdir $(addsuffix .c,$(basename $@))))

BKSH: $(BuiltDO) $(ParentDO) $(SystemDO) $(PromptDO) $(ManagerDO) $(DataabsDO) $(TopDO) $(InputDO) $(SignalDO)
	gcc -o BKSH Object_Files/*.o -g


$(ParentDO): $(ParentD)
	gcc -c $(ParentOD) -o $@ -g

$(SystemDO): $(SystemD)
	gcc -c $(SystemOD) -o $@ -g

$(PromptDO): $(PromptD)
	gcc -c $(PromptOD) -o $@ -g

$(BuiltDO): $(BuiltD)
	gcc -c $(BuiltOD) -o $@ -g

$(ManagerDO): $(ManagerD)
	gcc -c $(ManagerOD) -o $@ -g

$(DataabsDO): $(DataabsD)
	gcc -c $(DataabsOD) -o $@ -g

$(TopDO): $(TopD)
	gcc -c $(TopOD) -o $@ -g

$(InputDO): $(InputD)
	gcc -c $(InputOD) -o $@ -g

$(SignalDO): $(SignalD)
	gcc -c $(SignalOD) -o $@ -g

clean:
	rm -f BKSH Object_Files/*.o