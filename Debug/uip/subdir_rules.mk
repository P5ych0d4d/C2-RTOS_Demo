################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
uip/psock.obj: ../uip/psock.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="uip/psock.d_raw" --obj_directory="uip" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uip/timer_e.obj: ../uip/timer_e.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="uip/timer_e.d_raw" --obj_directory="uip" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uip/uip-fw.obj: ../uip/uip-fw.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="uip/uip-fw.d_raw" --obj_directory="uip" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uip/uip-neighbor.obj: ../uip/uip-neighbor.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="uip/uip-neighbor.d_raw" --obj_directory="uip" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uip/uip-split.obj: ../uip/uip-split.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="uip/uip-split.d_raw" --obj_directory="uip" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uip/uip.obj: ../uip/uip.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="uip/uip.d_raw" --obj_directory="uip" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uip/uip_arp.obj: ../uip/uip_arp.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="uip/uip_arp.d_raw" --obj_directory="uip" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uip/uiplib.obj: ../uip/uiplib.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 -me -Ooff --opt_for_speed=2 --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/portable/CCS/ARM_CM3" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/uip" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/WebServer" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/driverlib" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/Source_App/LCD/inc" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo" --include_path="D:/workspace_1.8.0/C2-RTOS_Demo/FreeRTOS/include" -g --gcc --define=ccs --define="ccs" --define=PART_LM3S6965 --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="uip/uiplib.d_raw" --obj_directory="uip" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


