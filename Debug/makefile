################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/Tools/TexasInstruments/ccs800/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./Lab01.obj" \
"./galvo.obj" \
"./menu.obj" \
"./pictures.obj" \
"./snake.obj" \
"./tm4c129encpdt_startup_ccs.obj" \
"./writing.obj" \
"../tm4c129encpdt.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \
-l"C:/Tools/TexasInstruments/TivaWare_C_Series-2.1.4.178/driverlib/ccs/Debug/driverlib.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
galvo_API.out \

EXE_OUTPUTS__QUOTED += \
"galvo_API.out" \

BIN_OUTPUTS += \
galvo_API.bin \

BIN_OUTPUTS__QUOTED += \
"galvo_API.bin" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "galvo_API.out"

# Tool invocations
galvo_API.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"C:/Tools/TexasInstruments/ccs800/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --define=ccs="ccs" --define=PART_TM4C129ENCPDT -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"galvo_API.map" --heap_size=0 --stack_size=512 -i"C:/Tools/TexasInstruments/ccs800/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/lib" -i"C:/Tools/TexasInstruments/ccs800/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="galvo_API_linkInfo.xml" --rom_model -o "galvo_API.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

galvo_API.bin: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"C:/Tools/TexasInstruments/ccs800/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armhex"  -o "galvo_API.bin" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "Lab01.obj" "galvo.obj" "menu.obj" "pictures.obj" "snake.obj" "tm4c129encpdt_startup_ccs.obj" "writing.obj" 
	-$(RM) "Lab01.d" "galvo.d" "menu.d" "pictures.d" "snake.d" "tm4c129encpdt_startup_ccs.d" "writing.d" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-"C:/Tools/TexasInstruments/ccs800/ccsv8/utils/tiobj2bin/tiobj2bin" "galvo_API.out" "galvo_API.bin" "C:/Tools/TexasInstruments/ccs800/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armofd" "C:/Tools/TexasInstruments/ccs800/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armhex" "C:/Tools/TexasInstruments/ccs800/ccsv8/utils/tiobj2bin/mkhex4bin"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

