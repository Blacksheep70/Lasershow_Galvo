################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Lab01.obj: ../Lab01.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/Tools/TexasInstruments/ccs800/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Alex/workspace_v8/galvo_API" --include_path="C:/Tools/TexasInstruments/ccs800/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --include_path="C:/Tools/TexasInstruments/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c129exl" --include_path="C:/Tools/TexasInstruments/TivaWare_C_Series-2.1.4.178" --define=ccs="ccs" --define=PART_TM4C129ENCPDT -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="Lab01.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

galvo.obj: ../galvo.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/Tools/TexasInstruments/ccs800/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Alex/workspace_v8/galvo_API" --include_path="C:/Tools/TexasInstruments/ccs800/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --include_path="C:/Tools/TexasInstruments/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c129exl" --include_path="C:/Tools/TexasInstruments/TivaWare_C_Series-2.1.4.178" --define=ccs="ccs" --define=PART_TM4C129ENCPDT -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="galvo.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

menu.obj: ../menu.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/Tools/TexasInstruments/ccs800/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Alex/workspace_v8/galvo_API" --include_path="C:/Tools/TexasInstruments/ccs800/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --include_path="C:/Tools/TexasInstruments/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c129exl" --include_path="C:/Tools/TexasInstruments/TivaWare_C_Series-2.1.4.178" --define=ccs="ccs" --define=PART_TM4C129ENCPDT -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="menu.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

pictures.obj: ../pictures.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/Tools/TexasInstruments/ccs800/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Alex/workspace_v8/galvo_API" --include_path="C:/Tools/TexasInstruments/ccs800/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --include_path="C:/Tools/TexasInstruments/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c129exl" --include_path="C:/Tools/TexasInstruments/TivaWare_C_Series-2.1.4.178" --define=ccs="ccs" --define=PART_TM4C129ENCPDT -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="pictures.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

snake.obj: ../snake.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/Tools/TexasInstruments/ccs800/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Alex/workspace_v8/galvo_API" --include_path="C:/Tools/TexasInstruments/ccs800/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --include_path="C:/Tools/TexasInstruments/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c129exl" --include_path="C:/Tools/TexasInstruments/TivaWare_C_Series-2.1.4.178" --define=ccs="ccs" --define=PART_TM4C129ENCPDT -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="snake.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

tm4c129encpdt_startup_ccs.obj: ../tm4c129encpdt_startup_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/Tools/TexasInstruments/ccs800/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Alex/workspace_v8/galvo_API" --include_path="C:/Tools/TexasInstruments/ccs800/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --include_path="C:/Tools/TexasInstruments/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c129exl" --include_path="C:/Tools/TexasInstruments/TivaWare_C_Series-2.1.4.178" --define=ccs="ccs" --define=PART_TM4C129ENCPDT -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="tm4c129encpdt_startup_ccs.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

writing.obj: ../writing.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/Tools/TexasInstruments/ccs800/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Alex/workspace_v8/galvo_API" --include_path="C:/Tools/TexasInstruments/ccs800/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --include_path="C:/Tools/TexasInstruments/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c129exl" --include_path="C:/Tools/TexasInstruments/TivaWare_C_Series-2.1.4.178" --define=ccs="ccs" --define=PART_TM4C129ENCPDT -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="writing.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


